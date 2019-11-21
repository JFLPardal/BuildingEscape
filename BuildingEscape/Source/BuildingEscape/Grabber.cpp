// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber ready"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotator);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotator.Vector() * Reach;
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Cyan, false, 0.f, 0.f, 5.f);
	
	FHitResult Hit;
	FCollisionQueryParams CollisionQueryParams{ FName(TEXT("")), false, GetOwner()};
	GetWorld()->LineTraceSingleByObjectType(
				Hit, 
				PlayerViewPointLocation, 
				LineTraceEnd, 
				FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
				CollisionQueryParams
	);

	AActor* Actor = Hit.GetActor();
	if (Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(Actor->GetName()));
	}
}

