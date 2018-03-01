// Fill out your copyright notice in the Description page of Project Settings.

#include "Trigger.h"
#include "RMovingPlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (!ensure(TriggerVolume != nullptr)) return;
	
		RootComponent = TriggerVolume;
		
}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATrigger::OnOverlapEnd);
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ATrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
 {
	//UE_LOG(LogTemp, Warning, TEXT("Activated"));
	for (ARMovingPlatform* Platform : PlatformsToTrigger)
		 {
		Platform->AddActiveTrigger();
		}
	}

void ATrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
 {
	//UE_LOG(LogTemp, Warning, TEXT("Deactivated"));
	for (ARMovingPlatform* Platform : PlatformsToTrigger)
		 {
		Platform->RemoveActiveTrigger();
		}

	}
