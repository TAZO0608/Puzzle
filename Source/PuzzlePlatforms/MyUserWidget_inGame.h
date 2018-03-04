// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyInterface.h"
#include "Components/Button.h"
#include "MyUserWidget_inGame.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMyUserWidget_inGame : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool Initialize() override;
public:
	void SetMenuInterface(IMyInterface* MenuInterface);
	void Teardown();
	IMyInterface* MenuInterface;
private:
	UPROPERTY(meta = (BindWidget))
		class UButton* Quit;
	UPROPERTY(meta = (BindWidget))
		class UButton* Back;

	UFUNCTION()
		void Back_F();
	UFUNCTION()
		void Quit_F();
	
	
};
