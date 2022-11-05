// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBuilding/BaseHolder.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

UCLASS()
class PROJECTTECTONIC_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveX(float AxisValue);
	void MoveY(float AxisValue);

	void RotateX(float AxisValue);
	void RotateY(float AxisValue);

	void DoJump();
	void ToggleCrouch();
	void Sprint();

	float ViewArrowPitchRotation;

	bool bIsSprinting;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UArrowComponent* ViewArrow;

	UPROPERTY(EditAnywhere)
	UCameraComponent* FPSCamera;

	UPROPERTY(EditAnywhere)
	float LookSensitivity;

	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	ABaseHolder* ActiveBase;
};
