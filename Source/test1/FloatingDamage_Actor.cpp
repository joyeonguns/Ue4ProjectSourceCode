// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingDamage_Actor.h"

// Sets default values
AFloatingDamage_Actor::AFloatingDamage_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TEXT"));
}

// Called when the game starts or when spawned
void AFloatingDamage_Actor::BeginPlay()
{
	Super::BeginPlay();
	lifeTime = 1.0f;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("SPAWN DAMAGE!!!"));
}

// Called every frame
void AFloatingDamage_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	lifeTime -= DeltaTime;
	if (lifeTime <= 0.0f) {
		Destroy();
	}
}

void AFloatingDamage_Actor::SetDamage(float takedamage)
{
	lifeTime = 1.0f;
	damage = damage = FText::AsNumber(takedamage); 
	TextRender->SetText(damage);
}

