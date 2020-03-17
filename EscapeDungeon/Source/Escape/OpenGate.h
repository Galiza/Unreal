// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenGate.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenGate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenGate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CloseGate(float DeltaTime);
	void OpenGate(float DeltaTime);
	float TotalMassOfActors() const;
	void FindPressurePlate();
	void FindTreasure();
	bool IsTreasureOnPedestal(float DeltaTime);
	void SlideGate(float CurrentPos);

private: 
	float InitialPos;
	float CurrentPos;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .5f;
		
	UPROPERTY(EditAnywhere)
	float ClosePos = 0.f;

	UPROPERTY(EditAnywhere)
	float OpenDoorVelocity = 1.f;

	UPROPERTY(EditAnywhere)
	float CloseDoorVelocity = 2.f;

	UPROPERTY(EditAnywhere)
	float MassThatOpens = 100.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* Treasure = nullptr;
};
