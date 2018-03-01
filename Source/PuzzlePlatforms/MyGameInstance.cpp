// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"


UMyGameInstance::UMyGameInstance(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

