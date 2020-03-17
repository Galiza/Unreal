// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenGate.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenGate::UOpenGate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenGate::BeginPlay()
{
	Super::BeginPlay();

	InitialPos = GetOwner()->GetActorLocation().Z;
	CurrentPos = InitialPos;
	
	FindPressurePlate();
	FindTreasure();
}

void UOpenGate::FindTreasure() 
{
	if(!Treasure) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the component and no Treasure linked to it!"), *GetOwner()->GetName());
	}
}

void UOpenGate::FindPressurePlate()
{
	if (!PressurePlate) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenGate component and no PressurePlate linked to it!"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenGate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (TotalMassOfActors() > MassThatOpens || PressurePlate->IsOverlappingActor(Treasure))
	{
		OpenGate(DeltaTime);
		
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseGate(DeltaTime);
		}
	}
}

float UOpenGate::TotalMassOfActors() const 
{
	float TotalMass = 0.f;

	// Find All Overlapping Actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) {return TotalMass;}
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (AActor* Actor : OverlappingActors) 
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

void UOpenGate::OpenGate(float DeltaTime)
{
	CurrentPos = FMath::FInterpTo(CurrentPos, InitialPos, DeltaTime, OpenDoorVelocity);
	SlideGate(CurrentPos);
}

void UOpenGate::CloseGate(float DeltaTime)
{
	CurrentPos = FMath::FInterpTo(CurrentPos, ClosePos, DeltaTime, OpenDoorVelocity);
	SlideGate(CurrentPos);
}

void UOpenGate::SlideGate(float CurrentPos) 
{
	FVector GatePosition = GetOwner()->GetActorLocation();
	GatePosition.Z = CurrentPos;
	GetOwner()->SetActorLocation(GatePosition);
}