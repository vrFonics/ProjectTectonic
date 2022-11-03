// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComponent_Parent.h"
#include "GameFramework/Actor.h"
#include "BaseHolder.generated.h"

UCLASS()
class PROJECTTECTONIC_API ABaseHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseHolder();

	void AddComponentAtLocation(TSubclassOf<ABaseComponent_Parent> ComponentClass, FVector Location);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void GenerateGridPointsAroundComponent(ABaseComponent_Parent* Component);
	void GeneratePointIfNonExistent(FVector Location);
	
	TMap<FVector, ABaseComponent_Parent*>* BaseComponentMap;

	FVector* TestVector;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TMap<FVector, ABaseComponent_Parent*>* GetBaseComponentMap();

	float ComponentSize;
};
