// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget_inGame.h"


bool  UMyUserWidget_inGame::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(Back != nullptr)) return false;
	Back->OnClicked.AddDynamic(this, &UMyUserWidget_inGame::Back_F);
	if (!ensure(Quit != nullptr)) return false;
	Quit->OnClicked.AddDynamic(this, &UMyUserWidget_inGame::Quit_F);

	

	return true;
}
void  UMyUserWidget_inGame::SetMenuInterface(IMyInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}
void UMyUserWidget_inGame::Teardown()
{
	this->RemoveFromViewport();

	UWorld * World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController * PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;
}
void  UMyUserWidget_inGame::Back_F() 
{
	Teardown();
}
void  UMyUserWidget_inGame::Quit_F() 
{
	Teardown();
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->ToMainMenu();
}
