// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectTectonicGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTECTONIC_API AProjectTectonicGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
};
