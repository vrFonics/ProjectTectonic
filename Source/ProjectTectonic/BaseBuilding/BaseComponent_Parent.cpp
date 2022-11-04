// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseComponent_Parent.h"

// Sets default values
ABaseComponent_Parent::ABaseComponent_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseComponentMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseComponentMesh"));
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
	FVector GridLocation = *MapOfComponents.FindKey(this);
}

// Called every frame
void ABaseComponent_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

