// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UArrowComponent* RootArrow;

	UDataTable* DynamicMeshDataTable;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void UpdateNeighbors(TMap<FVector, ABaseComponent_Parent*> MapOfComponents);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateDynamicMesh();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasBaseMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasDynamicMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> DynamicMeshes;

	UPROPERTY(BlueprintReadOnly)
	TMap<FVector, ABaseComponent_Parent*> NeighborsMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* BaseComponentMesh;
};
