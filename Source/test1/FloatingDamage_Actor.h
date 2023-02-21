// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "FloatingDamage_Actor.generated.h"

UCLASS()
class TEST1_API AFloatingDamage_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingDamage_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDamage(float takedamage);
	

private:
	FText damage;
	float lifeTime;

	UPROPERTY(VisibleAnywhere)
		UTextRenderComponent* TextRender;
};
