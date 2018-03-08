// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "UObject/ConstructorHelpers.h"
#include "ServerROW.h"
#include "Components/TextBlock.h"

UMyUserWidget::UMyUserWidget(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
 {
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr)) return;
	
		ServerRowClass = ServerRowBPClass.Class;
	}
bool UMyUserWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(Host != nullptr))return false;
	Host->OnClicked.AddDynamic(this, &UMyUserWidget::OpenHostMenu);

	if (!ensure(CancelHostMenuButton != nullptr)) return false;
	CancelHostMenuButton->OnClicked.AddDynamic(this, &UMyUserWidget::OpenMainMenu);
	
	if (!ensure(ConfirmHostMenuButton != nullptr)) return false;
	ConfirmHostMenuButton->OnClicked.AddDynamic(this, &UMyUserWidget::HostServer);

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


void UMyUserWidget::SetServerList(TArray<FServerData> ServerNames)
{
	
		UWorld * World = this->GetWorld();
		if (!ensure(World != nullptr)) return;
		
			ServerList->ClearChildren();
			uint32 i = 0;
		for (const FServerData& ServerData : ServerNames)
			 {
			UServerROW* Row = CreateWidget<UServerROW>(World, ServerRowClass);
			if (!ensure(Row != nullptr)) return;

			
			Row->ServerName->SetText(FText::FromString(ServerData.Name));
			Row->hostname->SetText(FText::FromString(ServerData.HostUsername));
			FString FractionText = FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers);
			Row->fraction->SetText(FText::FromString(FractionText));
			Row->Setup(this, i);
			++i;
				ServerList->AddChild(Row);
		}
}

void UMyUserWidget::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}
void UMyUserWidget::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); ++i)
		 {
		auto Row = Cast<UServerROW>(ServerList->GetChildAt(i));
		if (Row != nullptr)
			 {
			Row->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
			}
		}
}


 void UMyUserWidget::EnterServer() 
 {
	 if (SelectedIndex.IsSet()&& MenuInterface != nullptr)
		  {
		 UE_LOG(LogTemp, Warning, TEXT("Selected index %d."), SelectedIndex.GetValue());
		 MenuInterface->Enter(SelectedIndex.GetValue());
		 }
	 else
		  {
		 UE_LOG(LogTemp, Warning, TEXT("Selected index not set."));
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
		FString ServerName = ServerBoxName->Text.ToString();
		MenuInterface->Host(ServerName);
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
	if (MenuInterface != nullptr) {
		MenuInterface->RefreshServerList();
		
	}

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
void  UMyUserWidget::OpenHostMenu()
{
	MenuSwitcher->SetActiveWidget(HostMenu);
}