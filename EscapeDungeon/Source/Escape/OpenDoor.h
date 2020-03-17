// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void RotateDoor(float CurrentYaw);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void FindPressurePlate();

	// Check whether sound has played
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

private:
	
	float CurrentYaw;
	float InitialYaw;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float OpenDoorVelocity = 1.f;

	UPROPERTY(EditAnywhere)
	float CloseDoorVelocity = 2.f;

	UPROPERTY(EditAnywhere)
	float MassThatOpens = 100.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
};
