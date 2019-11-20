// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		OpenDoor();
		LastDoorOpenTime = CurrentTime;
	}
	if (LastDoorOpenTime + CloseDelay < CurrentTime)
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0, OpenAngle, 0));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0, CloseAngle, 0));
}

