// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPS_Character.h"
#include <Engine/Classes/Components/BoxComponent.h>
#include <Engine/Classes/Components/SkeletalMeshComponent.h>
#include "Weapon_Actor.generated.h"

UCLASS()
class TEST1_API AWeapon_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Actor(const class FObjectInitializer& ObjectInitializer);

	void SetOwningPawn(class ATPS_Character* WeaponOwner);
	void AttachMeshToPawn();
	void OnEquip(const class AWeapon_Actor* LastWeapon);
	
	void ApplyAttack();
	void ApplyCollision();
	void DeleteCollision();

private:
	UPROPERTY(VisibleDefaultsOnly, Category=weapon)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = weapon)
	class UBoxComponent* WeaponCollision;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = weapon)
	class ATPS_Character* MyOwner;

public:	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
