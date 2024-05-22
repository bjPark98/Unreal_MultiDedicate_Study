// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetworkCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ANetworkCharacter

UParticleSystem* ANetworkCharacter::mHitParticle = nullptr;
USoundBase* ANetworkCharacter::mHitSound = nullptr;

ANetworkCharacter::ANetworkCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	static ConstructorHelpers::FObjectFinder<UParticleSystem>	HitParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonMinions/FX/Particles/Minions/Minion_melee/FX/Impacts/P_Minion_Impact_Default.P_Minion_Impact_Default'"));

	if (HitParticleAsset.Succeeded())
		mHitParticle = HitParticleAsset.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase>	HitSoundAsset(TEXT("/Script/Engine.SoundWave'/Game/Sound/Fire1.Fire1'"));

	if (HitSoundAsset.Succeeded())
		mHitSound = HitSoundAsset.Object;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ANetworkCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (HasAuthority())
	{
		mName = TEXT("플레이어");
		mAttack = 50;
		mDefense = 20;
		mHP = 500;
		mHPMax = 500;
		mMP = 100;
		mMPMax = 100;
	}
}

void ANetworkCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 리플리케이트 되는 모든 변수들을 여기에 등록한다.
	// DOREPLIFETIME은 현재 클래스 타입, 변수이름을 작성한다.
	DOREPLIFETIME(ANetworkCharacter, mName);
	DOREPLIFETIME(ANetworkCharacter, mAttack);
	DOREPLIFETIME(ANetworkCharacter, mDefense);
	DOREPLIFETIME(ANetworkCharacter, mHP);
	DOREPLIFETIME(ANetworkCharacter, mHP);
	DOREPLIFETIME(ANetworkCharacter, mMP);
	DOREPLIFETIME(ANetworkCharacter, mMPMax);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ANetworkCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANetworkCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANetworkCharacter::Look);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ANetworkCharacter::NormalAttack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANetworkCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ANetworkCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ANetworkCharacter::NormalAttack(const FInputActionValue& Value)
{
	AttackCheck();
}

void ANetworkCharacter::AttackCheck_Implementation()
{
	UE_LOG(Network, Warning, TEXT("Server Check"));
	GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, TEXT("Server Check"));

	FCollisionQueryParams	param(NAME_None, false, this);

	//AKDT1PlayerState* State = GetPlayerState<AKDT1PlayerState>();

	FVector	StartLocation = GetActorLocation();

	FVector	EndLocation = StartLocation + GetActorForwardVector() * 200.f;

	TArray<FHitResult>	resultArray;
	bool IsCollision = GetWorld()->SweepMultiByChannel(resultArray,
		StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel5,
		FCollisionShape::MakeSphere(50.f), param);

	AttackDebugDraw(IsCollision, StartLocation, EndLocation);

	if (IsCollision)
	{
		for (int32 i = 0; i < resultArray.Num(); ++i)
		{
			FDamageEvent	DmgEvent;

			resultArray[i].GetActor()->TakeDamage((float)mAttack, DmgEvent,
				GetController(), this);

			// 이 함수는 파티클을 스폰시키고 스폰된 파티클 재생이 완료되면
			// 자동으로 제거해준다.
			AttackEffect(resultArray[i].ImpactPoint);
			/*UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mHitParticle,
				resultArray[i].ImpactPoint, FRotator::ZeroRotator,
				true);*/

			//UGameplayStatics::SpawnDecalAtLocation(GetWorld(), Mtrl, Size, Location)

			// 이펙트 출력 및 사운드 재생.
			/*FActorSpawnParameters	SpawnParam;

			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(
				resultArray[i].ImpactPoint,
				resultArray[i].ImpactNormal.Rotation(), SpawnParam);

			Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonMinions/FX/Particles/Minions/Minion_melee/FX/Impacts/P_Minion_Impact_Default.P_Minion_Impact_Default'"));
			Effect->SetSoundAsset(TEXT("/Script/Engine.SoundWave'/Game/ParagonKwang/Characters/Heroes/Kwang/Sounds/SoundWaves/Kwang_Effort_Swing_01.Kwang_Effort_Swing_01'"));*/
		}
	}
}

void ANetworkCharacter::AttackDebugDraw_Implementation(bool IsCollision, const FVector& Start,
	const FVector& End)
{
#if ENABLE_DRAW_DEBUG

	// 구를 그린다.
	FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (Start + End) / 2.f,
		200.f / 2.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 3.f);

#endif
}

float ANetworkCharacter::TakeDamage(float DamageAmount, 
	struct FDamageEvent const& DamageEvent, class AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator,
		DamageCauser);

	DamageAmount = DamageAmount - mDefense;
	DamageAmount = DamageAmount < 1.f ? 1.f : DamageAmount;

	AddHP(-DamageAmount);


	return DamageAmount;
}

void ANetworkCharacter::AttackEffect_Implementation(const FVector& Location)
{
	if (!HasAuthority())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mHitParticle,
			Location, FRotator::ZeroRotator, true);

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), mHitSound, Location);

		//UGameplayStatics::SpawnDecalAtLocation()
	}
}

void ANetworkCharacter::AddHP_Implementation(float HP)
{
	mHP += HP;

	if (mHP < 0)
		mHP = 0;

	if (HasAuthority())
	{
		UE_LOG(Network, Warning, TEXT("HP : %d"), mHP);
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
			FString::Printf(TEXT("HP : %d"), mHP));
	}
}
