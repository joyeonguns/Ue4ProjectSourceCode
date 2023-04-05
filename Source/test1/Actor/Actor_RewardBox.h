// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon_Actor.h"
#include "TPS_Character.h"
#include "Actor_RewardBox.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnIteraction_Delegate);
DECLARE_MULTICAST_DELEGATE(FOnEndReward_Delegate);

UCLASS()
class TEST1_API AActor_RewardBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_RewardBox();

protected:

public:	

	// OverlapEvent
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;


public:

	void SetBuff(int32 code);

	void GetHeart();

	void GetEnergy();

	void GetArcane();

	void GetDia();

	void GetShield();


	// Reward Modelling
	AActor* GetModel();

	

private:
	// Spawn ItemClass
	UPROPERTY(EditAnywhere, Category = spwn)
		TArray<TSubclassOf<AActor>> WeaponArray;	

	// Spawn BuffClass
	UPROPERTY(EditAnywhere, Category = spwn)
		TArray<TSubclassOf<AActor>> BuffArray;
		
	AActor* ModelObj;

	UPROPERTY(EditAnywhere, Category = spwn)
		class UBoxComponent* InteractionCollision;


private:
	class ATPS_Character* player;

public:
	FOnIteraction_Delegate OnIteraction;
	FOnEndReward_Delegate OnEndReward;

};
