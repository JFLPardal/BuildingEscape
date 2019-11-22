// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

class ATriggerVolume;
class AActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable) FOnOpenRequest OnOpenRequest;
private:
	UPROPERTY(VisibleAnywhere) float OpenAngle = -180.f;
	UPROPERTY(VisibleAnywhere) float CloseAngle = -90.f;
	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere) float CloseDelay = .5f;
	UPROPERTY(EditAnywhere) float MassToTriggerPlate = 50.f;
	
	AActor* Owner = nullptr;
	float LastDoorOpenTime;

	float GetMassOfActorsOnPlate();
};
