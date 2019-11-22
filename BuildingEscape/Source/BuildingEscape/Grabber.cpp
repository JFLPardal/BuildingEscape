// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{ 
	Super::BeginPlay();

	SetupReferencesToComponents();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandler != nullptr && PhysicsHandler->GrabbedComponent != nullptr)
	{
		PhysicsHandler->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::Grab()
{
	if (PhysicsHandler == nullptr) { return; }
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ActorToGrab = HitResult.GetActor();

	if (ActorToGrab != nullptr)
	{
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		PhysicsHandler->GrabComponentAtLocation(ComponentToGrab, NAME_None, ActorToGrab->GetActorLocation());
	}
}

void UGrabber::Release()
{
	if (PhysicsHandler == nullptr) { return; }
	PhysicsHandler->ReleaseComponent();
}

void UGrabber::SetupReferencesToComponents()
{
	SetupPhysicsHandlerComponent();
	SetupInputComponent();	
}

void UGrabber::SetupPhysicsHandlerComponent()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandler == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandler Component is attached to %s"), *(GetOwner()->GetName()));
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No InputComponent is attached to %s"), *(GetOwner()->GetName()));
	}
	else
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult HitResult; 
	FCollisionQueryParams CollisionQueryParams{ FName(TEXT("")), false, GetOwner() };
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		CollisionQueryParams
	);
	return HitResult;
}

FVector UGrabber::GetReachLineStart() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotator);
	return PlayerViewPointLocation;

}

FVector UGrabber::GetReachLineEnd() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotator);
	return PlayerViewPointLocation + PlayerViewPointRotator.Vector() * Reach;
}
