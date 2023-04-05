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
	void AttachMeshToPawn(FName AttachName);
	void OnEquip(const class AWeapon_Actor* LastWeapon);
	
	// 공격함수
	void ApplyAttack();
	// 컬리전 적용
	void ApplyCollision();
	// 컬리전 해제
	void DeleteCollision();

private:
	UPROPERTY(VisibleDefaultsOnly, Category=weapon)
	USkeletalMeshComponent* WeaponMesh;

	// 공격 컬리전
	UPROPERTY(VisibleDefaultsOnly, Category = weapon)
	class UBoxComponent* WeaponCollision;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = weapon)
	class ATPS_Character* MyOwner;

public:	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


	// 스폰 잔상 오브젝트
	UPROPERTY(EditAnywhere, Category = Spawn)
		TSubclassOf<AActor_GhostTail> SpawnGhostClass;

	// 잔상 생성
	void SpawnGhostTail();

	// 잔상효과 타임핸들러 
	FTimerHandle TH_Ghost;
};
