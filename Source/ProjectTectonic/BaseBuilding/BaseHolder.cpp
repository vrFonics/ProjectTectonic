// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHolder.h"

// Sets default values
ABaseHolder::ABaseHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

