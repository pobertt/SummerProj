#include "BaseGameMode.h"
#include "BaseGameState.h"

ABaseGameMode::ABaseGameMode()
{
	GameStateClass = ABaseGameState::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/Character/BP_FPSCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

int32 ABaseGameMode::GetTestCount() const
{
	return GetGameState<ABaseGameState>()->TestCount;
}

void ABaseGameMode::SetTestCount(int32 newTestCount)
{
	GetGameState<ABaseGameState>()->TestCount = newTestCount;
}

void ABaseGameMode::StartPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Start Play called"));

	StartPlayEvent();

	/* Initialize stuff here */

	GetWorld()->GetAuthGameMode()->GetGameState<ABaseGameState>()->TestCount = 150;

	Super::StartPlay();
}

void ABaseGameMode::StartPlayEvent_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("StartPlayEvent Default Implementation called"));
}
