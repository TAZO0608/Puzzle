// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyInterface.h"
#include "MyUserWidget.generated.h"

USTRUCT()
 struct FServerData
 {
	GENERATED_BODY()
	
	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
	};

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
		UMyUserWidget(const FObjectInitializer & ObjectInitializer);
		 protected:
			virtual bool Initialize() override;
			TSubclassOf<class UUserWidget> ServerRowClass;
			TOptional<uint32> SelectedIndex;
			void UpdateChildren();
	public:
		void SelectIndex(uint32 Index);
		void SetMenuInterface(IMyInterface* MenuInterface);
		void Teardown();
		void SetServerList(TArray<FServerData> ServerNames);
		private:
		UPROPERTY(meta = (BindWidget))
		class UWidget* HostMenu;
		
		UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* ServerBoxName;
	
		UPROPERTY(meta = (BindWidget))
		class UButton* CancelHostMenuButton;
	
		UPROPERTY(meta = (BindWidget))
		 class UButton* ConfirmHostMenuButton;


		UPROPERTY(meta = (BindWidget))
		 class UButton* Host;
	
		UPROPERTY(meta = (BindWidget))
		class UButton* Join;
		UPROPERTY(meta = (BindWidget))
		class UButton* Enter;
		UPROPERTY(meta = (BindWidget))
			class UButton* Exit;
		UFUNCTION()
		void HostServer();
		UFUNCTION()
		void EnterServer();
		IMyInterface* MenuInterface;
		//UPROPERTY(meta = (BindWidget))
		//class UEditableTextBox* IPAddressField;
		UPROPERTY(meta = (BindWidget))
		 class UButton* Cancel;
		UPROPERTY(meta = (BindWidget))
		class UPanelWidget* ServerList;
		UFUNCTION()
			void Exit_F();
		
		UPROPERTY(meta = (BindWidget))
		 class UWidgetSwitcher* MenuSwitcher;
		
		UPROPERTY(meta = (BindWidget))
		class UWidget* main_menu;
		
		UPROPERTY(meta = (BindWidget))
		 class UWidget* join_menu;

		UFUNCTION()
		void OpenJoinMenu();
		
		UFUNCTION()
		void OpenMainMenu();
		UFUNCTION()
		 void OpenHostMenu();
};
