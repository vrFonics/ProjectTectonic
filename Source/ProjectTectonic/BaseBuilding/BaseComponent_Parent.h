// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseComponent_Parent.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void UpdateNeighbors(TMap<FVector, ABaseComponent_Parent*> MapOfComponents);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateDynamicMesh();
	
	bool bHasBaseMesh;

	UPROPERTY(BlueprintReadOnly)
	TMap<FVector, ABaseComponent_Parent*> NeighborsMap;
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* BaseComponentMesh;
};
