// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseComponent_Parent.h"

#include "EngineUtils.h"

// Sets default values
ABaseComponent_Parent::ABaseComponent_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Root"));
	RootArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	BaseComponentMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseComponentMesh"));
	BaseComponentMeshComponent->AttachToComponent(RootArrow, FAttachmentTransformRules::KeepRelativeTransform);

	FSoftObjectPath DynamicMeshDataTablePath("DataTable'/Game/DataTables/DT_MeshArrangements.DT_MeshArrangements'");
	
	DynamicMeshDataTable = Cast<UDataTable>(DynamicMeshDataTablePath.TryLoad());
	if (DynamicMeshDataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Problems."));
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
	//BaseComponentMeshComponent->SetStaticMesh(BaseComponentMesh);
}

void ABaseComponent_Parent::UpdateNeighbors(TMap<FVector, ABaseComponent_Parent*> MapOfComponents)
{
	FVector GridLocation = *MapOfComponents.FindKey(this);
	NeighborsMap.Empty();
	FVector NeighborLocations [6] = {
		GridLocation + FVector(1, 0, 0),
		GridLocation + FVector(-1, 0, 0),
		GridLocation + FVector(0, 1, 0),
		GridLocation + FVector(0, -1, 0),
		GridLocation + FVector(0, 0, 1),
		GridLocation + FVector(0, 0, -1)
	};
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
	if (bHasDynamicMesh)
	{
		UpdateDynamicMesh();
	}
}

void ABaseComponent_Parent::UpdateDynamicMesh_Implementation()
{
	FString DynamicMeshCode = "";
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
	int Code = FCString::Atoi(*DynamicMeshCode);
	int CodeDecimal = 0;
	int CurrentDigit = 0;
	int Temp;

	while (Code != 0)
	{
		Temp = Code % 10;
		Code /= 10;
		CodeDecimal += Temp * pow(2, CurrentDigit);
		CurrentDigit++;
	}

	static const FString ContextString(TEXT(""));
	FDynamicMeshArrangement MeshArrangement = *DynamicMeshDataTable->FindRow<FDynamicMeshArrangement>(FName(FString::FromInt(CodeDecimal)), ContextString);

	BaseComponentMeshComponent->SetStaticMesh(DynamicMeshes[MeshArrangement.MeshIndex]);
	BaseComponentMeshComponent->SetRelativeRotation(MeshArrangement.MeshRotation);
}

// Called every frame
void ABaseComponent_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

