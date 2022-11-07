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

	//Attempts to generate empty grid points at every possible attach location for a given grid point
	UFUNCTION()
	void GenerateGridPointsAroundGridPoint(FVector Location);
	//Generates an empty grid point at a specified grid location if one does not already exist
	UFUNCTION()
	void GeneratePointIfNonExistent(FVector Location);

	//DEVELOPER ONLY - TESTING PURPOSES - LAGS LIKE ****
	void CreateDebugActorsAtEmptyGridSpaces();

	//Stores components attached to this base as a value and their location in the base grid as a key
	UPROPERTY()
	TMap<FVector, ABaseComponent_Parent*> BaseComponentMap;

	//For use in CreateDebugActorsAtEmptyGridSpaces
	UPROPERTY()
	TArray<AActor*> DebugObjects;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Attempts to add a component at a location if a: specified grid location exists and b: a component does not already exist at that location
	UFUNCTION(BlueprintCallable, Category="Basebuilding")
	void AddComponentAtLocation(TSubclassOf<ABaseComponent_Parent> ComponentClass, FVector Location);
	//Attempts to remove a component at a location if a component does exist at that location
	UFUNCTION(BlueprintCallable, Category="Basebuilding")
	void RemoveComponentAtLocation(FVector Location);

	//Takes a component and returns the grid location at at offset relative to this component's grid location. If passed a zero vector as an offset this will return the grid location of the component
	UFUNCTION(BlueprintCallable, Category="Basebuilding")
	FVector GetLocationRelativeToComponent(ABaseComponent_Parent* BaseComponent, FVector OffsetDirection);
	
	UFUNCTION()
	TMap<FVector, ABaseComponent_Parent*> GetBaseComponentMap();

	//Class of object used to represent grid point in CreateDebugActorsAtEmptyGridSpaces
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DebugObjectClass;

	//Size of each grid space. All meshes in a base component should fit within this grid space to prevent overlap
	UPROPERTY(EditAnywhere)
	float ComponentSize;

	//Name of this individual base, mostly used for debug purposes
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString BaseName;
};
