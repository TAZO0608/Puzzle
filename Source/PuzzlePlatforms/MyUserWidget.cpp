// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

 bool UMyUserWidget::Initialize()
 {
	bool Success = Super::Initialize();
	if (!Success) return false;
	
	if (!ensure(Host != nullptr))return false;
	Host->OnClicked.AddDynamic(this, &UMyUserWidget::HostServer);

	if (!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMyUserWidget::OpenJoinMenu);
	
	if (!ensure(Cancel != nullptr)) return false;
	Cancel->OnClicked.AddDynamic(this, &UMyUserWidget::OpenMainMenu);

	if (!ensure(Enter != nullptr)) return false;
	Enter->OnClicked.AddDynamic(this, &UMyUserWidget::EnterServer);

	if (!ensure(Exit != nullptr)) return false;
	Exit->OnClicked.AddDynamic(this, &UMyUserWidget::Exit_F);

	return true;
	}

 void UMyUserWidget::EnterServer() 
 {
	 if(MenuInterface != nullptr)
	 {
		 if (!ensure(IPAddressField != nullptr)) return;
		 const FString& Address = IPAddressField->GetText().ToString();
		 MenuInterface->Enter(Address);
	 }

 }
 void UMyUserWidget::Teardown()
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
void UMyUserWidget::HostServer()
 {
	if (MenuInterface != nullptr)
		{
		MenuInterface->Host();
		}
}

void UMyUserWidget::SetMenuInterface(IMyInterface* MenuInterface)
 {
	this->MenuInterface = MenuInterface;
	}

void UMyUserWidget::OpenJoinMenu()
 {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(join_menu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(join_menu);
	}

void UMyUserWidget::OpenMainMenu()
 {
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(main_menu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(main_menu);
	}

void  UMyUserWidget::Exit_F()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController * PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}