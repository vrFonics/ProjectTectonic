// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PortableComponent_Parent.h"
#include "Components/ArrowComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "BaseComponent_Parent.generated.h"

USTRUCT(BlueprintType)
struct FDynamicMeshArrangement : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	FDynamicMeshArrangement()
		: MeshIndex(0)
	, MeshRotation(FRotator(0, 0, 0))
	{}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MeshIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator MeshRotation;
};

UCLASS(Blueprintable)
class PROJECTTECTONIC_API ABaseComponent_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseComponent_Parent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseComponentMeshComponent;

	UPROPERTY()
	UArrowComponent* RootArrow;

	//Data table that stores the mesh arrangements for dynamic component meshes
	UPROPERTY()
	UDataTable* DynamicMeshDataTable;

	//Stores all portable components that have been placed on this component
	UPROPERTY()
	TArray<APortableComponent_Parent*> AttachedPortableComponents;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Updates the neighbors of this component
	void UpdateNeighbors(TMap<FVector, ABaseComponent_Parent*> MapOfComponents);
	//Updates the mesh of this component to connect to its neighbors
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateDynamicMesh();
	//Destroys this component
	UFUNCTION()
	void DestroyBaseComponent();

	//Specifies whether or not this component needs a mesh (for example the core component has no visual representation)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasBaseMesh;
	//Specifies whether or not this component has a mesh library to allow it to dynamically connect to adjacent meshes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasDynamicMesh;

	//TODO put file with required mesh order in this array somewhere for future reference
	//Fill with meshes if component has a dynamic mesh, otherwise leave empty
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> DynamicMeshes;

	//Stores all neighboring components in the base grid
	UPROPERTY(BlueprintReadOnly)
	TMap<FVector, ABaseComponent_Parent*> NeighborsMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BaseComponentMesh;
};
