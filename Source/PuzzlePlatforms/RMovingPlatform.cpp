// Fill out your copyright notice in the Description page of Project Settings.

#include "RMovingPlatform.h"



ARMovingPlatform::ARMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
	
}

void ARMovingPlatform::BeginPlay()
 {
	Super::BeginPlay();
	
		if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
		
	}
		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	}

void ARMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector Location = GetActorLocation();

			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}

			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += Speed * DeltaTime * Direction;
			SetActorLocation(Location);
		}
	}
}
void ARMovingPlatform::AddActiveTrigger()
 {
	ActiveTriggers++;
	}
void ARMovingPlatform::RemoveActiveTrigger()
 {
	if (ActiveTriggers > 0)
		 {
		ActiveTriggers--;
	}
}
