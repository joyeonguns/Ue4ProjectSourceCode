// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterStat_DataTable.h"
#include "Character_Stat_Component.h"
#include "Components/WidgetComponent.h"
#include "FloatingDamage_Widget.h"
#include "FloatingDamage_Actor.h"
#include "TPSAnimInstance.h"
#include "Basic_Character.generated.h"



UCLASS()
class TEST1_API ABasic_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasic_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	virtual void OnHit(float InputDamage, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;



	UPROPERTY(EditAnywhere, Category=HP)
	float myHealth;

	UPROPERTY(EditAnywhere, Category = HP)
	float myMaxHealth;

	// ***** Anim ****
	UPROPERTY()
		class UTPSAnimInstance* Anim;

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* DefaultAttack_Montage;

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* BeHit_AnimMontage;

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* BeElectric_AnimMontage;

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* Dash_AnimMontage;

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* Disarm_AnimMontage;

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* Armed_AnimMontage;

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* Death_AnimMontage;
	// ***** Anim ****

	bool isCanMove;
	bool isCanJump;
	bool isCanRotate;

	bool isDash;
	bool isDuringAttack;

	bool bCanNextAttack;

	bool bDisarm;

	bool bShocking;
	float shockTime;

	bool bDead;

	bool broll;

	int32 MaxCombo;
	int32 currentCombo;

	// 오라 스폰 클래스
	UPROPERTY(EditAnywhere, Category = Aura)
		TSubclassOf<AActor> ArcaneAuraClass;
	UPROPERTY(EditAnywhere, Category = Aura)
		TSubclassOf<AActor> HeartAuraClass;
	UPROPERTY(EditAnywhere, Category = Aura)
		TSubclassOf<AActor> ShieldeAuraClass;
	UPROPERTY(EditAnywhere, Category = Aura)
		TSubclassOf<AActor> DiaAuraClass;
	UPROPERTY(EditAnywhere, Category = Aura)
		TSubclassOf<AActor> EnergyAuraClass;

	class AActor* ApplyAuraInstance;

	UPROPERTY(EditAnywhere, Category = Aura)
		TSubclassOf<AActor> BurnDebuffClass;
	UPROPERTY(EditAnywhere, Category = Aura)
		TSubclassOf<AActor> ElectricDebuffClass;
	UPROPERTY(EditAnywhere, Category = Aura)
		TSubclassOf<AActor> WetDebuffClass;

	class AActor* ApplyDebuffAuraInstance;

	// 전투 데이터
	float realMoveSpeed;

	float Move_Speed = 1.0;
	float Attack_Speed = 1.0;
	int32 Skill_Acceleration = 0;

	const int32 AddSpeed = 20;
	const int32 AddLife = 1;
	const int32 AddShield = 5;
	const float AddRecoverHp = 0.8f;
	const float DefaultRunSpeed = 600;
	const float DefaultWalkSpeed = 300;

	bool bBurnning;
	bool bElectric;
	bool bWetting;

	float BurnTime;
	float ElectricTime;
	float WetTime;

	float WetDebuff = 0;

	const float DefaultBurnTime = 5.0f;
	const float DefaultElectricTime = 5.0f;
	const float DefaultWetTime = 10.0f;

	int32 ApplyBuffCode;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void DieCharacter();

	virtual void DestroyCharacter();

	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UCharacter_Stat_Component* Status_Component;
	

	void DefaultAttack(float speed);

	virtual void AttackEnd();
	
	virtual void TakeShock();
	void EndShock();

	bool GetCheckShocking();

	void SetMoveSpeed();

	bool GetbDead();


	// Buff
	virtual void ApplyBuff_Heart();

	virtual void ApplyBuff_Energy();

	virtual void ApplyBuff_Arcane();

	virtual void ApplyBuff_Dia();

	virtual void ApplyBuff_Shield();


	virtual void ResetBuff();

	UFUNCTION()
	void ResetAura();

	void SpwAura(TSubclassOf<AActor> AuraClass);

	// DeBuff
	void DebuffTick(float deltaTime);

	void SpwnDebuffAura(TSubclassOf<AActor> AuraClass);
	void ResetDebuffAura();

	void GetDeBuff_Burn();
	void GetDeBuff_Electric();
	void GetDeBuff_Wet();

	void ApplyDeBuff_Burn();
	void ApplyDeBuff_Electric();
	void ApplyDeBuff_Wet();

	void DifuseBuff();


private:
	FTimerHandle TH_burn;
	FTimerHandle TH_elec;
	FTimerHandle TH_wet;

	

};
