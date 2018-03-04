// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyInterface.h"
#include "MyGameInstance.generated.h"

/**
*
*/
UCLASS()
class PUZZLEPLATFORMS_API UMyGameInstance : public UGameInstance , public IMyInterface
{
	GENERATED_BODY()


public:
	UMyGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	void LoadMenu();
	UFUNCTION(BlueprintCallable)
	 void InGameLoadMenu();

	UFUNCTION(Exec)
		void Host() override;
	
		UFUNCTION(Exec)
		 void Enter(const FString& Address) override;
		UFUNCTION()
		 void ToMainMenu()override;
private:
	TSubclassOf<class UUserWidget> MenuClass;
	class UMyUserWidget* Menu;
	class UMyUserWidget_inGame * Menu_inGame;
	TSubclassOf<class UUserWidget> InGameMenuClass;

};
