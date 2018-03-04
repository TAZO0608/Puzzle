// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyInterface.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
		 protected:
			virtual bool Initialize() override;
	public:
		void SetMenuInterface(IMyInterface* MenuInterface);
		void Teardown();
		private:
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
		UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* IPAddressField;
		UPROPERTY(meta = (BindWidget))
		 class UButton* Cancel;
		
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
};
