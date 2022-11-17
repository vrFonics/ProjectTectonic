// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_BaseBuildingTool.h"

// Sets default values for this component's properties
UAC_BaseBuildingTool::UAC_BaseBuildingTool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_BaseBuildingTool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAC_BaseBuildingTool::CreatePortableComponentHologram()
{
	
}

void UAC_BaseBuildingTool::CreateBaseComponentHologram()
{
	
}

// Called every frame
void UAC_BaseBuildingTool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_BaseBuildingTool::ToggleToolActive()
{
	if (bToolActivated)
	{
		bToolActivated = false;
		return;
	}
	else
	{
		bToolActivated = true;
	}
}

