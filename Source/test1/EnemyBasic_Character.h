// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Basic_Character.h"
#include "HP_UserWidget.h"
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include "EnemyBasic_Character.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnDeadDelegate);

UCLASS()
class TEST1_API AEnemyBasic_Character : public ABasic_Character
{
	GENERATED_BODY()
	
public:
	AEnemyBasic_Character();

	void SpawnDamage(float damage, bool critical);
	void Set_HpBar();
	void DrawHpBar();
	void Delete_HpBar();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Attack();

	virtual void AttackEnd() override;
	
	virtual void DieCharacter() override;

	FOnAttackEndDelegate OnAttackEnd;
	FOnDeadDelegate OnDeadDelegate;

	virtual void AttackCheck();

	float GetAttackRange();

	void CharacterDead();

	void SetPrize(int32 newPrize);

	int32 GetPrize();


protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PossessedBy(AController* newController) override;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* Hp_UI;

	UPROPERTY(EditAnywhere, Category = Damage)
		TSubclassOf<AFloatingDamage_Actor> Damage_Actor;

	UPROPERTY(EditAnywhere, Category = Damage)
		TSubclassOf<class UFloatingDamage_Widget> Damage_Ui;

	bool bOnHpBar;
	float lifeTime_HpBar;

	UPROPERTY(EditAnywhere, Category = Attack)
		float AttackRange;
	UPROPERTY(EditAnywhere, Category = Attack)
		float AttackRadius;

	bool bAttacking;

private:
	int32 prize = 1;


public: 

};
