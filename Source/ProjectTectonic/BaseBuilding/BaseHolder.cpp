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
	if (BaseComponentMap.FindRef(Location) != nullptr)
	{
		return;
	}
	if (!BaseComponentMap.Contains(Location))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("BaseComponentMap does not contain") + Location.ToString());
		return;
	}
	*BaseComponentMap.Find(Location) = GetWorld()->SpawnActor<ABaseComponent_Parent>(ComponentClass, GetActorLocation() + (Location * ComponentSize), FRotator(0, 0, 0));
	GenerateGridPointsAroundGridPoint(Location);
	BaseComponentMap.FindRef(Location)->UpdateNeighbors(BaseComponentMap);
	for (auto& Component : BaseComponentMap.FindRef(Location)->NeighborsMap)
	{
		if (Component.Value != nullptr)
		{
			Component.Value->UpdateNeighbors(BaseComponentMap);
		}
	}
	CreateDebugActorsAtEmptyGridSpaces();
}

void ABaseHolder::RemoveComponentAtLocation(FVector Location)
{
	ABaseComponent_Parent* ComponentToDestroy = BaseComponentMap.FindRef(Location);
	if (ComponentToDestroy == nullptr)
	{
		return;
	}
	auto& ComponentNeighbors = ComponentToDestroy->NeighborsMap;
	ComponentToDestroy->Destroy();
	*BaseComponentMap.Find(Location) = nullptr;

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

FVector ABaseHolder::GetLocationAdjacentToComponent(ABaseComponent_Parent* BaseComponent, FVector Direction)
{
	return *BaseComponentMap.FindKey(BaseComponent) + Direction;
}

// Called when the game starts or when spawned
void ABaseHolder::BeginPlay()
{
	Super::BeginPlay();
	BaseComponentMap.Add(FVector(0, 0, 0), GetWorld()->SpawnActor<ABaseComponent_Parent>(ABaseComponent_CoreComponent::StaticClass(), this->GetActorLocation(), FRotator(0, 0, 0)));
	GenerateGridPointsAroundGridPoint(FVector (0, 0, 0));
	CreateDebugActorsAtEmptyGridSpaces();

	if (BaseName == "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("BaseHolder has no BaseName. Please ensure it has a name and that all BaseHolders in the world have a unique name to ensure Developer Basebuilding Menu will properly function."));
	}
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

