// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_ItemModel.h"

// Sets default values
AActor_ItemModel::AActor_ItemModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActor_ItemModel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActor_ItemModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

