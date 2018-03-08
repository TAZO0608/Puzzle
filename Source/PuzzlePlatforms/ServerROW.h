// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerROW.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerROW : public UUserWidget
{
	GENERATED_BODY()
public:
		UPROPERTY(meta = (BindWidget))
		class UTextBlock* ServerName;
		UPROPERTY(meta = (BindWidget))
		class UTextBlock* hostname;
		
		UPROPERTY(meta = (BindWidget))
		 class UTextBlock* fraction;
		void Setup(class UMyUserWidget* Parent, uint32 Index);
		UPROPERTY(BlueprintReadOnly)
		bool Selected = false;
private:
		UPROPERTY(meta = (BindWidget))
		 class UButton* RowButton;
	
		UPROPERTY()
		class UMyUserWidget* Parent;

		uint32 Index;
		
		UFUNCTION()
		 void OnClicked();
	
};
