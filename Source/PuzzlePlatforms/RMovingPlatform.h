// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "RMovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ARMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
	
public:
	ARMovingPlatform();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float Speed = 20;
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
		 FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();
	private:
		FVector GlobalTargetLocation;
		FVector GlobalStartLocation;

		UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;
	
};
