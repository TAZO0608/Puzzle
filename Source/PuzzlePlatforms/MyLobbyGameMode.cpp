// Fill out your copyright notice in the Description page of Project Settings.

#include "MyLobbyGameMode.h"
#include "TimerManager.h"

#include "MyGameInstance.h"

void AMyLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	++NumberOfPlayers;
	
		if (NumberOfPlayers >= 2)
		 {
			GetWorldTimerManager().SetTimer(GameStartTimer, this, &AMyLobbyGameMode::StartGame, 10);
		}
}

void AMyLobbyGameMode::Logout(AController* Exiting)
 {
	Super::Logout(Exiting);
	--NumberOfPlayers;
	}
void AMyLobbyGameMode::StartGame()
 {
	auto GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
		if (GameInstance == nullptr) return;
	
		GameInstance->StartSession();
	
		UWorld * World = GetWorld();
	if (!ensure(World != nullptr)) return;
	
		bUseSeamlessTravel = true;
		World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}

