// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseComponent_Parent.h"

#include "EngineUtils.h"

// Sets default values
ABaseComponent_Parent::ABaseComponent_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates an arrow to use as the root component
	RootArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Root"));
	RootArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	BaseComponentMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseComponentMesh"));
	BaseComponentMeshComponent->AttachToComponent(RootArrow, FAttachmentTransformRules::KeepRelativeTransform);

	//Finds the data table for dynamic mesh arrangements and loads it for use in updating the mesh.
	const FSoftObjectPath DynamicMeshDataTablePath("DataTable'/Game/DataTables/DT_MeshArrangements.DT_MeshArrangements'");
	DynamicMeshDataTable = Cast<UDataTable>(DynamicMeshDataTablePath.TryLoad());
	if (DynamicMeshDataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Dynamic Mesh Arrangment data table not found at specified path."));
	}
}

// Called when the game starts or when spawned
void ABaseComponent_Parent::BeginPlay()
{
	Super::BeginPlay();
	if (!bHasBaseMesh)
	{
		return;
	}
	if (BaseComponentMesh == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No Mesh Assigned for BaseComponentMesh. If this Base Component does not have a Base Mesh please ensure bHasBaseMesh is set to false."));
		return;
	}
	BaseComponentMeshComponent->SetStaticMesh(BaseComponentMesh);
}

void ABaseComponent_Parent::UpdateNeighbors(TMap<FVector, ABaseComponent_Parent*> MapOfComponents)
{
	//Gets the location of this component in the base grid
	const FVector GridLocation = *MapOfComponents.FindKey(this);
	//Empties the neighbors map
	NeighborsMap.Empty();
	//Stores grid points at an offset of 1 and -1 in each axis direction
	FVector NeighborLocations [6] = {
		GridLocation + FVector(1, 0, 0),
		GridLocation + FVector(-1, 0, 0),
		GridLocation + FVector(0, 1, 0),
		GridLocation + FVector(0, -1, 0),
		GridLocation + FVector(0, 0, 1),
		GridLocation + FVector(0, 0, -1)
	};
	//Checks if each location exists in the base grid, and if so adds it to the neighbors map
	for (FVector Location : NeighborLocations)
	{
		if (MapOfComponents.Contains(Location))
		{
			NeighborsMap.Add(Location - GridLocation, MapOfComponents.FindRef(Location));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Neighbor Location not in supplied TMap. Grid points may have failed to properly generate."));
		}
	}
	//If this component has a dynamic mesh we almost always need to update the mesh after updating neighbors.
	if (bHasDynamicMesh)
	{
		UpdateDynamicMesh();
	}
}

void ABaseComponent_Parent::DestroyBaseComponent()
{
	GetWorld()->DestroyActor(this);
}

void ABaseComponent_Parent::UpdateDynamicMesh_Implementation()
{
	//This is most likely not the best way to do this
	//Creates an empty string
	FString DynamicMeshCode = "";
	//Checks the neighbors in positive and negative x and y. If a neighbor exists append a 1, if it doesn't append a 0
	TArray<FVector> Directions = {
		FVector(1, 0, 0),
		FVector(-1, 0, 0),
		FVector(0, 1, 0),
		FVector(0, -1, 0),
	};
	for (FVector Direction : Directions)
	{
		if (NeighborsMap.FindRef(Direction) == nullptr)
		{
			DynamicMeshCode.Append("0");
		}
		else
		{
			DynamicMeshCode.Append("1");
		}
	}
	//Converts this string into an integer
	int Code = FCString::Atoi(*DynamicMeshCode);

	//Takes the integer and reads it as a binary value, then converts that binary value to decimal
	int CodeDecimal = 0;
	int CurrentDigit = 0;
	int Temp = 0;
	while (Code != 0)
	{
		Temp = Code % 10;
		Code /= 10;
		CodeDecimal += Temp * pow(2, CurrentDigit);
		CurrentDigit++;
	}

	//Uses the decimal value as a key for the datatable to find the correct mesh to use to connect to the neighbors
	static const FString ContextString(TEXT(""));
	const FDynamicMeshArrangement MeshArrangement = *DynamicMeshDataTable->FindRow<FDynamicMeshArrangement>(FName(FString::FromInt(CodeDecimal)), ContextString);
	BaseComponentMeshComponent->SetStaticMesh(DynamicMeshes[MeshArrangement.MeshIndex]);
	BaseComponentMeshComponent->SetRelativeRotation(MeshArrangement.MeshRotation);
}

// Called every frame
void ABaseComponent_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

