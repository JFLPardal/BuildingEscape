// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

class ATriggerVolume;
class AActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

	UPROPERTY(BlueprintAssignable) FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable) FDoorEvent OnClose;
private:
	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere) float MassToTriggerPlate = 50.f;
	
	AActor* Owner = nullptr;

	float GetMassOfActorsOnPlate();
};
