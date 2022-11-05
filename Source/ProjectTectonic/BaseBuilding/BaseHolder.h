// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseComponent_Parent.h"
#include "GameFramework/Actor.h"
#include "BaseHolder.generated.h"

UCLASS(Blueprintable)
class PROJECTTECTONIC_API ABaseHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseHolder();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void GenerateGridPointsAroundGridPoint(FVector Location);
	void GeneratePointIfNonExistent(FVector Location);

	//DEVELOPER ONLY - TESTING PURPOSES
	void CreateDebugActorsAtEmptyGridSpaces();
	
	TMap<FVector, ABaseComponent_Parent*> BaseComponentMap;

	FVector* TestVector;

	TArray<AActor*> DebugObjects;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Basebuilding")
	void AddComponentAtLocation(TSubclassOf<ABaseComponent_Parent> ComponentClass, FVector Location);
	UFUNCTION(BlueprintCallable, Category="Basebuilding")
	void RemoveComponentAtLocation(FVector Location);

	UFUNCTION(BlueprintCallable, Category="Basebuilding")
	FVector GetLocationAdjacentToComponent(ABaseComponent_Parent* BaseComponent, FVector Direction);

	TMap<FVector, ABaseComponent_Parent*>* GetBaseComponentMap();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DebugObjectClass;

	UPROPERTY(EditAnywhere)
	float ComponentSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString BaseName;
};
