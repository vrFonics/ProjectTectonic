// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "AC_BaseBuildingTool.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTECTONIC_API UAC_BaseBuildingTool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_BaseBuildingTool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void CreatePortableComponentHologram();
	UFUNCTION(BlueprintCallable)
	void CreateBaseComponentHologram();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ToggleToolActive();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* ViewArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bToolActivated;
};
