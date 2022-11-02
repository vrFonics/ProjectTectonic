// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ViewArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ViewArrow"));
	ViewArrow->SetRelativeLocation(FVector(0, 0, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * 0.75));
	ViewArrow->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPSCamera->AttachToComponent(ViewArrow, FAttachmentTransformRules::KeepRelativeTransform);

	AutoReceiveInput = EAutoReceiveInput::Player0;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	ViewArrowPitchRotation = 0.0f;
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstPersonCharacter::MoveX(float AxisValue)
{
	GetMovementComponent()->AddInputVector(GetActorRightVector() * AxisValue);
}

void AFirstPersonCharacter::MoveY(float AxisValue)
{
	GetMovementComponent()->AddInputVector(GetActorForwardVector() * AxisValue);
}

void AFirstPersonCharacter::RotateX(float AxisValue)
{
	GetCapsuleComponent()->AddRelativeRotation(FRotator(0, AxisValue * LookSensitivity, 0));
}

void AFirstPersonCharacter::RotateY(float AxisValue)
{
	ViewArrowPitchRotation += AxisValue * LookSensitivity;
	ViewArrowPitchRotation = UKismetMathLibrary::ClampAngle(ViewArrowPitchRotation, -89.9, 89.9);
	ViewArrow->SetRelativeRotation(FRotator(ViewArrowPitchRotation, ViewArrow->GetRelativeRotation().Yaw, ViewArrow->GetRelativeRotation().Roll));
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    InputComponent->BindAxis("MoveX", this, &AFirstPersonCharacter::MoveX);
	InputComponent->BindAxis("MoveY", this, &AFirstPersonCharacter::MoveY);
	InputComponent->BindAxis("RotateX", this, &AFirstPersonCharacter::RotateX);
	InputComponent->BindAxis("RotateY", this, &AFirstPersonCharacter::RotateY);
}

