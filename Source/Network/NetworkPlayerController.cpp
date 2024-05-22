
#include "NetworkPlayerController.h"
#include "NetworkCharacter.h"
#include "UI/MainWidget.h"
#include "Network/NetworkManager.h"
#include "Network/NetSession.h"
#include "Thread/ThreadMgr.h"
#include "Thread/ChatThread.h"
#include "Network/PacketQueue.h"

ANetworkPlayerController::ANetworkPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>	UIClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/UI_Main.UI_Main_C'"));

	if (UIClass.Succeeded())
		mMainWidgetClass = UIClass.Class;

	bShowMouseCursor = true;

	// 클라이언트에 이 액터를 복제할지 판단.
	SetReplicates(true);

	// 이 액터의 움직임이 클라이언트에 복제되는지 판단.
	SetReplicateMovement(true);
}

void ANetworkPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 이 함수의 리턴이 true일 경우 서버, false일 경우 클라이언트 이다.
	if (!HasAuthority())
	{
		FInputModeGameAndUI	InputMode;

		SetInputMode(InputMode);

		if (IsValid(mMainWidgetClass))
		{
			mMainWidget = CreateWidget<UMainWidget>(GetWorld(), mMainWidgetClass);
			mMainWidget->AddToViewport();
		}


		// 채팅서버에 연결한다.
		CNetworkManager::GetInst()->Connect(TEXT("ChatSession"),
			TEXT("127.0.0.1"), 10010);

		CNetSession* Session = CNetworkManager::GetInst()->FindSession(TEXT("ChatSession"));

		FThreadInfo* ThreadInfo = CThreadMgr::GetInst()->CreateThread<CChatThread>(TEXT("ChatThread"));

		if (ThreadInfo)
		{
			ThreadInfo->Worker->SetLoop(true);
			((CChatThread*)ThreadInfo->Worker)->SetSession(Session);

			// 스레드를 동작시켜준다.
			ThreadInfo->Worker->Start();
			//CThreadMgr::GetInst()->SuspendThread(TEXT("LoginThread"), false);

			mQueue = CNetworkManager::GetInst()->FindPacketQueue(TEXT("ChatPacketQueue"));
		}
	}
}

void ANetworkPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	/*ANetworkCharacter* Char = Cast<ANetworkCharacter>(aPawn);

	Char->SetTeamNumber(mTeamNumber);*/
}

void ANetworkPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority() && mQueue)
	{
		if (!mQueue->Empty())
		{
			int32	Header = 0, Length = 0;
			uint8	Packet[1024] = {};

			mQueue->Pop(Header, Length, Packet);

			TCHAR	ChatMsg[1024] = {};

			switch (Header)
			{
			case EChatType::Normal:
				FMemory::Memcpy(ChatMsg, Packet, Length);

				GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red,
					ChatMsg);

				mMainWidget->SetChatNormal(ChatMsg);

				break;
			}
		}
	}
}

void ANetworkPlayerController::SetTeamNumber_Implementation(int Number)
{
	mTeamNumber = Number;
}

void ANetworkPlayerController::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetworkPlayerController, mTeamNumber);
}
