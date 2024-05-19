// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BaseGameState.generated.h"

/**
 * 
 */
UCLASS()
class SUMMERPROJ_API ABaseGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ABaseGameState();
	virtual ~ABaseGameState() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TestCount;
};
