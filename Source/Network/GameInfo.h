#pragma once

#include "EngineMinimal.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Net/UnrealNetwork.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

DECLARE_LOG_CATEGORY_EXTERN(Network, Log, All);

UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	None,
	Knight,
	Archer,
	Magicion
};

enum class EAttackCollider : uint8
{
	Left,
	Right,
	Both
};
