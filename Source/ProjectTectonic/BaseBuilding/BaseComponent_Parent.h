// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHolder.h"
#include "GameFramework/Actor.h"
#include "BaseComponent_Parent.generated.h"

UCLASS()
class PROJECTTECTONIC_API ABaseComponent_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseComponent_Parent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateNeighbors();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseComponentMeshComponent;

	TMap<FVector, TSubclassOf<ABaseComponent_Parent>>* NeighborsMap;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool bHasBaseMesh;
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* BaseComponentMesh;

	ABaseHolder* ParentHolder;
};
