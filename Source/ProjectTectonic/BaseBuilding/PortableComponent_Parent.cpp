// Fill out your copyright notice in the Description page of Project Settings.


#include "PortableComponent_Parent.h"

// Sets default values
APortableComponent_Parent::APortableComponent_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APortableComponent_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortableComponent_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortableComponent_Parent::DestroyPortableComponent()
{
	//TODO Return used resources to player when breaking down component
	GetWorld()->DestroyActor(this);
}

