// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"
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
	void StartSession();
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	void MyLoadMenu();
	UFUNCTION(BlueprintCallable)
	 void InGameLoadMenu();
	void RefreshServerList() override;
	UFUNCTION(Exec)
		void Host(FString name) override;
	
		UFUNCTION(Exec)
		void Enter(uint32 index) override;
		UFUNCTION()
		 void ToMainMenu()override;
private:
	TSubclassOf<class UUserWidget> MenuClass;
	class UMyUserWidget* Menu;
	class UMyUserWidget_inGame * Menu_inGame;
	TSubclassOf<class UUserWidget> InGameMenuClass;
	
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
