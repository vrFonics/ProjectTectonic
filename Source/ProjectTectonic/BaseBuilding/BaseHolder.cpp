// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHolder.h"

#include "BaseComponents/BaseComponent_CoreComponent.h"

// Sets default values
ABaseHolder::ABaseHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseHolder::AddComponentAtLocation(TSubclassOf<ABaseComponent_Parent> ComponentClass, FVector Location)
{
	//Returns if there is already a component at the given location or if the base does not have an empty grid point at that location
	if (BaseComponentMap.FindRef(Location) != nullptr)
	{
		return;
	}
	if (!BaseComponentMap.Contains(Location))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("BaseComponentMap does not contain") + Location.ToString());
		return;
	}

	//Creates a base component at the grid location.
	*BaseComponentMap.Find(Location) = GetWorld()->SpawnActor<ABaseComponent_Parent>(ComponentClass, GetActorLocation() + (Location * ComponentSize), FRotator(0, 0, 0));
	//Generates new empty grid points around the new component
	GenerateGridPointsAroundGridPoint(Location);
	//Updates the neighbors of this component
	BaseComponentMap.FindRef(Location)->UpdateNeighbors(BaseComponentMap);
	//Updates the neighbors of all neighbors to this component
	for (auto& Component : BaseComponentMap.FindRef(Location)->NeighborsMap)
	{
		if (Component.Value != nullptr)
		{
			Component.Value->UpdateNeighbors(BaseComponentMap);
		}
	}
	//CreateDebugActorsAtEmptyGridSpaces();
}

void ABaseHolder::RemoveComponentAtLocation(FVector Location)
{
	//Returns if a component does not exist at the supplied location
	ABaseComponent_Parent* ComponentToDestroy = BaseComponentMap.FindRef(Location);
	if (ComponentToDestroy == nullptr)
	{
		return;
	}

	//Stores a reference to the neighbors of this component before destroying it so they can be updated after this component is destroyed
	auto& ComponentNeighbors = ComponentToDestroy->NeighborsMap;

	//Destroys this component and empties the grid location
	ComponentToDestroy->Destroy();
	*BaseComponentMap.Find(Location) = nullptr;

	//Updates all the neighbors of the neighbors if they are not empty grid spaces, and then generates empty grid points around the neighbors (generating empty grid points around neighbors is currently redundant) 
	for (auto& Element : ComponentNeighbors)
	{
		if (BaseComponentMap.Contains(Element.Key + Location) && BaseComponentMap.FindRef(Element.Key + Location) != nullptr)
		{
			if (Element.Value != nullptr)
			{
				Element.Value->UpdateNeighbors(BaseComponentMap);
			}
			GenerateGridPointsAroundGridPoint(Element.Key + Location);
		}
	}

	//Deprecated, loops through all elements in map to regenerate grid points. Was used before components kept track of their own neighbors.
	/*
	TArray<FVector> Keys;
	BaseComponentMap.GetKeys(Keys);
	for (FVector GridPointLocation : Keys)
	{
		if (BaseComponentMap.FindRef(GridPointLocation) != nullptr)
		{
			GenerateGridPointsAroundGridPoint(GridPointLocation);
		}
	}*/
}

FVector ABaseHolder::GetLocationRelativeToComponent(ABaseComponent_Parent* BaseComponent, FVector OffsetDirection)
{
	return *BaseComponentMap.FindKey(BaseComponent) + OffsetDirection;
}

TMap<FVector, ABaseComponent_Parent*> ABaseHolder::GetBaseComponentMap()
{
	return BaseComponentMap;
}

// Called when the game starts or when spawned
void ABaseHolder::BeginPlay()
{
	Super::BeginPlay();
	//Adds a core component at the origin of the base grid
	BaseComponentMap.Add(FVector(0, 0, 0), GetWorld()->SpawnActor<ABaseComponent_Parent>(ABaseComponent_CoreComponent::StaticClass(), this->GetActorLocation(), FRotator(0, 0, 0)));

	//Generates empty grid points around core component
	GenerateGridPointsAroundGridPoint(FVector (0, 0, 0));

	//CreateDebugActorsAtEmptyGridSpaces();

	//Alert for debugging if base was not given a name
	if (BaseName == "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("BaseHolder has no BaseName. Please ensure it has a name and that all BaseHolders in the world have a unique name to ensure Developer Basebuilding Menu will properly function."));
	}
}

void ABaseHolder::GenerateGridPointsAroundGridPoint(FVector Location)
{
	//Gets the position adjacent to supplied position both positive and negative for every axis
	FVector Locations [6] =
		{Location + FVector(1, 0, 0),
		Location + FVector(-1, 0, 0),
		Location + FVector(0, 1, 0),
		Location + FVector(0, -1, 0),
		Location + FVector(0, 0, 1),
		Location + FVector(0, 0, -1)};
	for (FVector GridPointTestLocation : Locations)
	{
		//For each adjacent position attempt to generate empty grid point
		GeneratePointIfNonExistent(GridPointTestLocation);
	}
}

void ABaseHolder::GeneratePointIfNonExistent(FVector Location)
{
	//Generates empty grid point if this location does not already exist within the grid
	if (!BaseComponentMap.Contains(Location))
	{
		BaseComponentMap.Add(Location, nullptr);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Location.ToString());
	}
}

void ABaseHolder::CreateDebugActorsAtEmptyGridSpaces()
{
	//Extremely bad performance and needs rewrite
	return;
	/*
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
	*/
}

// Called every frame
void ABaseHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}

