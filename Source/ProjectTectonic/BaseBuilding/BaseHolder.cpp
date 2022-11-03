// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHolder.h"

// Sets default values
ABaseHolder::ABaseHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
}

void ABaseHolder::AddComponentAtLocation(TSubclassOf<ABaseComponent_Parent> ComponentClass, FVector Location)
{
	*BaseComponentMap->Find(Location) = GetWorld()->SpawnActor<ABaseComponent_Parent>(ComponentClass, Location * ComponentSize, FRotator(0, 0, 0));
	BaseComponentMap->FindRef(Location)->UpdateNeighbors(BaseComponentMap);
}

// Called when the game starts or when spawned
void ABaseHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseHolder::GenerateGridPointsAroundComponent(ABaseComponent_Parent* Component)
{
	FVector TestLocation = *BaseComponentMap->FindKey(Component);
	FVector Locations [6] =
		{TestLocation + FVector(1, 0, 0),
		TestLocation + FVector(-1, 0, 0),
		TestLocation + FVector(0, 1, 0),
		TestLocation + FVector(0, -1, 0),
		TestLocation + FVector(0, 0, 1),
		TestLocation + FVector(0, 0, -1)};
	for (FVector GridPointTestLocation : Locations)
	{
		GeneratePointIfNonExistent(GridPointTestLocation);
	}
}

void ABaseHolder::GeneratePointIfNonExistent(FVector Location)
{
	bool PointAlreadyExists = false;
	
	//TODO fix syntax problems
	/*for (FVector GridPointLocation : BaseComponentMap->GetKeys)
	{
		if (Location == GridPointLocation)
		{
			PointAlreadyExists = true;
		}
	}*/
	if (!PointAlreadyExists)
	{
		BaseComponentMap->Add(Location, nullptr);
	}
}


// Called every frame
void ABaseHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}

