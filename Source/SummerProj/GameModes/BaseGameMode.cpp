#include "BaseGameMode.h"
// Fill out your copyright notice in the Description page of Project Settings.

ABaseGameMode::ABaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/BP_PlayerCharacter"));
}
