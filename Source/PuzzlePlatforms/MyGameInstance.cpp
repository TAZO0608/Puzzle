// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Trigger.h"
#include "OnlineSubsystem.h"
#include "MyUserWidget.h"
#include "MyUserWidget_inGame.h"
#include "Engine/Engine.h"
#include "OnlineSessionSettings.h"



UMyGameInstance::UMyGameInstance(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_mainmenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	
		MenuClass = MenuBPClass.Class;
		ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGame_menu"));
		if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
		
		InGameMenuClass = InGameMenuBPClass.Class;
}

void UMyGameInstance::Init()
{
	Super::Init();

	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Found subsystem %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			UE_LOG(LogTemp, Warning, TEXT("Found session interface"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMyGameInstance::OnFindSessionsComplete);
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMyGameInstance::OnJoinSessionComplete);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
	
}
void UMyGameInstance::RefreshServerList()
 {
	if (SessionSearch.IsValid())
	{
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
	}

void UMyGameInstance::Host(FString name)
{
	
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(TEXT("Game"));
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(TEXT("Game"));
		}
		else
		{
			FOnlineSessionSettings SessionSettings;
			if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
			{
				SessionSettings.bIsLANMatch = true;
			}
			else
			{
				SessionSettings.bIsLANMatch = false;
			}
			SessionSettings.NumPublicConnections = 2;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bUsesPresence = true;
			SessionSettings.Set(TEXT("ServerName"), name, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
			SessionInterface->CreateSession(0, TEXT("Game"), SessionSettings);
		}
		
	}
}
void UMyGameInstance::OnFindSessionsComplete(bool Success)
{
	if (Success && SessionSearch.IsValid() && Menu != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished Find Session"));
		TArray<FServerData> ServerNames;

		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session names: %s"), *SearchResult.GetSessionIdStr());
			FServerData data;
			data.Name = SearchResult.GetSessionIdStr();
			data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
			data.CurrentPlayers = data.MaxPlayers - SearchResult.Session.NumOpenPublicConnections;
			data.HostUsername = SearchResult.Session.OwningUserName;
			FString ServerName;
			if (SearchResult.Session.SessionSettings.Get(TEXT("ServerName"), ServerName))
			 {
				data.Name = ServerName;
			}
			else
			 {
				data.Name = "Could not find name.";
			}
			ServerNames.Add(data);
		}
		Menu->SetServerList(ServerNames);
	}
}
void UMyGameInstance::OnDestroySessionComplete(FName SessionName, bool Success) 
{
	if (Success)
	{
		if (SessionInterface.IsValid())
		{
			FOnlineSessionSettings SessionSettings;
			if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
			 {
				SessionSettings.bIsLANMatch = true;
			}
			else
			 {
				SessionSettings.bIsLANMatch = false;
			}
			SessionSettings.NumPublicConnections = 2;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bUsesPresence = true;

			SessionInterface->CreateSession(0, TEXT("Game"), SessionSettings);
		}
	}
}
void UMyGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
 {
	if (!Success)
		 {
		UE_LOG(LogTemp, Warning, TEXT("Could not create session"));
		return;
		}
	if (Menu != nullptr)
		{
		Menu->Teardown();
		}
	UEngine * Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		
			World->ServerTravel("/Game/Puzzle/Maps/Lobby?listen");
	}

void UMyGameInstance::Enter(uint32 Index)
 {
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;
	if (Menu != nullptr)
	{
	
		Menu->Teardown();
	}
	SessionInterface->JoinSession(0, TEXT("Game"), SessionSearch->SearchResults[Index]);
	                               //My Session Game
	}
void UMyGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
 {
	if (!SessionInterface.IsValid()) return;
	
		FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address)) {
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string."));
		return;
	}
	
	UEngine * Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
void UMyGameInstance::ToMainMenu() 
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);

}
void UMyGameInstance::MyLoadMenu()
 {
	if (!ensure(MenuClass != nullptr)) return;
	
	 Menu = CreateWidget<UMyUserWidget>(this, MenuClass);
	 if (!ensure(Menu != nullptr))
	 {
		 UE_LOG(LogTemp, Warning, TEXT("here"));
		 return;
	 }
	
	Menu->AddToViewport();
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	
	PlayerController->SetInputMode(InputModeData);
	
	PlayerController->bShowMouseCursor = true;

	Menu->SetMenuInterface(this);
}
void UMyGameInstance::InGameLoadMenu()
 {
	Menu_inGame = CreateWidget<UMyUserWidget_inGame>(this, InGameMenuClass);
	if (!ensure(Menu_inGame != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("here"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *InGameMenuClass->GetName());
	Menu_inGame->AddToViewport();
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu_inGame->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;

	Menu_inGame->SetMenuInterface(this);
	}
void  UMyGameInstance::StartSession()
 {
	if (SessionInterface.IsValid())
		 {
		SessionInterface->StartSession(TEXT("Game"));
		}
	}