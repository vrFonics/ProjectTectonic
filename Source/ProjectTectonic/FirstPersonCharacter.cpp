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
	ViewArrow->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ViewArrow->SetRelativeLocation(FVector(0, 0, GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * 0.75));
	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPSCamera->AttachToComponent(ViewArrow, FAttachmentTransformRules::KeepRelativeTransform);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	ViewArrowPitchRotation = 0.0f;

	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	
	bIsSprinting = false;
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstPersonCharacter::MoveX(float AxisValue)
{
	GetMovementComponent()->AddInputVector(GetCapsuleComponent()->GetRightVector() * AxisValue);
}

void AFirstPersonCharacter::MoveY(float AxisValue)
{
	GetMovementComponent()->AddInputVector(GetCapsuleComponent()->GetForwardVector() * AxisValue);
}

void AFirstPersonCharacter::RotateX(float AxisValue)
{
	GetController()->SetControlRotation(FRotator(GetControlRotation().Pitch, GetControlRotation().Yaw + (AxisValue * LookSensitivity), GetControlRotation().Roll));
}

void AFirstPersonCharacter::RotateY(float AxisValue)
{
	ViewArrowPitchRotation += AxisValue * LookSensitivity;
	ViewArrowPitchRotation = UKismetMathLibrary::ClampAngle(ViewArrowPitchRotation, -89.9, 89.9);
	ViewArrow->SetRelativeRotation(FRotator(ViewArrowPitchRotation, ViewArrow->GetRelativeRotation().Yaw, ViewArrow->GetRelativeRotation().Roll));
}

void AFirstPersonCharacter::DoJump()
{
	Jump();
}

void AFirstPersonCharacter::ToggleCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(BaseEyeHeight));

	}
	else
	{
		Crouch();
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(CrouchedEyeHeight));
	}
}

void AFirstPersonCharacter::Sprint()
{
	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
	else
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	}
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
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFirstPersonCharacter::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AFirstPersonCharacter::Sprint);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFirstPersonCharacter::DoJump);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AFirstPersonCharacter::ToggleCrouch);

}

