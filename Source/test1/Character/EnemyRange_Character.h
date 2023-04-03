// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBasic_Character.h"
#include "SPWArrow_Actor.h"
#include "EnemyRange_Character.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API AEnemyRange_Character : public AEnemyBasic_Character
{
	GENERATED_BODY()
	
public:
	AEnemyRange_Character();


	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Attack() override;

	virtual void AttackEnd() override;

	virtual void AttackCheck() override;

	void SpwArrow();

	USkeletalMeshComponent* GetSpecificPawnMesh() const;

	void Shutting();

	void DropArrow();

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = arrows)
		FName AttachName;


	// 화살 클래스
	UPROPERTY(EditDefaultsOnly, Category = arrows)
		TSubclassOf<class ASPWArrow_Actor> SpwArrowClass;
	
	class ASPWArrow_Actor* arrowInstance;
	
};
