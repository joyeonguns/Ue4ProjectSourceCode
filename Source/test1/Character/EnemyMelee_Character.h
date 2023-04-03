// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBasic_Character.h"
#include "EnemyMelee_Character.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API AEnemyMelee_Character : public AEnemyBasic_Character
{
	GENERATED_BODY()
	
public:
	AEnemyMelee_Character();


	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Attack() override;

	virtual void AttackEnd() override;
	//FOnAttackEndDelegate OnAttackEnd;

	virtual void AttackCheck() override;
};
