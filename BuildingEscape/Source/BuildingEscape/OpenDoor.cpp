// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

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
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (GetMassOfActorsOnPlate() > MassToTriggerPlate)
	{
		OpenDoor();
		LastDoorOpenTime = CurrentTime;
	}
	if (LastDoorOpenTime + CloseDelay < CurrentTime)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetMassOfActorsOnPlate()
{
	TArray<AActor*> ActorsOverlapping;
	PressurePlate->GetOverlappingActors(ActorsOverlapping);
	float TotalMass = 0.f; 
	for (const auto* Actor : ActorsOverlapping)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("%f"), TotalMass);
	return TotalMass;
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0, OpenAngle, 0));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0, CloseAngle, 0));
}

