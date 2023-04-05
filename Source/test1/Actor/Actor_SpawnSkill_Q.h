// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPS_Character.h"
#include "Actor_SpawnSkill_Q.generated.h"

UCLASS()
class TEST1_API AActor_SpawnSkill_Q : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_SpawnSkill_Q();

protected:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	class ATPS_Character* myOwner;
	float Damage;

public:	
	void SetOwner(class ATPS_Character* _myOwner);
	void SetDamage(float _damage);

	// 공격 속성
	UPROPERTY(EditAnywhere, Category=School)
		FString School;

};
