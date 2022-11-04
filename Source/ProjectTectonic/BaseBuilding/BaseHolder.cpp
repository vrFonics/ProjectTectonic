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
	*BaseComponentMap.Find(Location) = GetWorld()->SpawnActor<ABaseComponent_Parent>(ComponentClass, Location * ComponentSize, FRotator(0, 0, 0));
	BaseComponentMap.FindRef(Location)->UpdateNeighbors(BaseComponentMap);
}

// Called when the game starts or when spawned
void ABaseHolder::BeginPlay()
{
	Super::BeginPlay();
	BaseComponentMap.Add(FVector(0, 0, 0), nullptr);
	GenerateGridPointsAroundGridPoint(FVector (0, 0, 0));
	CreateDebugActorsAtEmptyGridSpaces();
}

void ABaseHolder::GenerateGridPointsAroundGridPoint(FVector Location)
{
	FVector Locations [6] =
		{Location + FVector(1, 0, 0),
		Location + FVector(-1, 0, 0),
		Location + FVector(0, 1, 0),
		Location + FVector(0, -1, 0),
		Location + FVector(0, 0, 1),
		Location + FVector(0, 0, -1)};
	for (FVector GridPointTestLocation : Locations)
	{
		GeneratePointIfNonExistent(GridPointTestLocation);
	}
}

void ABaseHolder::GeneratePointIfNonExistent(FVector Location)
{
	bool PointAlreadyExists = false;
	
	//TODO fix syntax problems
	TArray<FVector> Keys;
	BaseComponentMap.GetKeys(Keys);
	for (FVector GridPointLocation : Keys)
	{
		if (Location == GridPointLocation)
		{
			PointAlreadyExists = true;
		}
	}
	if (!PointAlreadyExists)
	{
		BaseComponentMap.Add(Location, nullptr);
	}
}

void ABaseHolder::CreateDebugActorsAtEmptyGridSpaces()
{
	for (AActor* Actor : DebugObjects)
	{
		DebugObjects.Remove(Actor);
		Actor->Destroy();
	}
	
	for (auto& MapElement : BaseComponentMap)
	{
		if (MapElement.Value == nullptr)
		{
			DebugObjects.Add(GetWorld()->SpawnActor<AActor>(DebugObjectClass, GetActorLocation() + (MapElement.Key * ComponentSize), FRotator(0, 0, 0)));
		}
	}
	
}

// Called every frame
void ABaseHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}

