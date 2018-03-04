// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Trigger.h"
#include "MyUserWidget.h"
#include "MyUserWidget_inGame.h"
#include "Engine/Engine.h"


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
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
	
}
void UMyGameInstance::Host()
 {
	if (Menu != nullptr)
		{
		Menu->Teardown();
		}
	UEngine * Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		
			World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}

void UMyGameInstance::Enter(const FString& Address)
 {

	if (Menu != nullptr)
	{
		Menu->Teardown();
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
void UMyGameInstance::LoadMenu()
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