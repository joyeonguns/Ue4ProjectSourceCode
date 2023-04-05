// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "Weapon_Actor.h"
#include "Basic_Character.h"
#include "HUD_UserWidget.h"
#include "TPSPlayerController.h"
#include "Actor_SpawnSkill_Q.h"
#include "Actor_GhostTail.h"
#include "TPS_Character.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInteraction_Delegate);


UCLASS()
class TEST1_API ATPS_Character : public ABasic_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPS_Character();

	// *** weapon ***
	USkeletalMeshComponent* GetSpecificPawnMesh() const;
	FName GetWeaponAttachPoint() const;
	void EquipWeapon(class AWeapon_Actor* Weapon);
	virtual void PostInitializeComponents() override;
	void SpawnDefaultInventory(int32 itemCode);
	// *** weapon ***
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ControllMode(int32 mode);

	// *** // weapon ***
	

	// 무기 부착소켓 이름
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName DisarmPoint;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName WeaponAttackPoint;

	TArray<class AWeapon_Actor*> Inventory;

	UPROPERTY(EditAnywhere, Category = Inventory)
	class AWeapon_Actor* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<TSubclassOf<class AWeapon_Actor>> DefaultInventoryClasses;

public:
	void AddWeapon(class AWeapon_Actor* Weapon);

	void SetCurrentWeapon(class AWeapon_Actor* NewWeapon, class AWeapon_Actor* LastWeapon);
	
	void EquipWeapon();

	void DisArmWeapon();

	virtual void TakeShock() override;
		
	// *** weapon // ***

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// ***  skill ***
	//	skill Q 번개배기
	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* Skill_Q_AnimMontage;

	UPROPERTY(EditAnywhere, Category = Skill)
		TArray<TSubclassOf<class AActor_SpawnSkill_Q>> Spw_SkillEffectClass_Q_Array;
	
	void SpwnObjSkill_Q();
	void SpwnObjSkill_Q_1();
	void SpwnObjSkill_Q_2();


	//	skill E 전진배기
	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* Skill_E_AnimMontage;

	void DashFront();
	void StopDash();

	
	// skill Rolling
	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* RollingFront_AnimMontage;
	
	void Rolling();

	void MoveRolling(float deltaTime);

	float RollingDuration = 0.7f;
	float currentRollingTime;
	

	FVector rollStartLoc;
	FVector rollEndLoc;

	FTimerHandle TH_roll;


	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;


	// 잔상 생성
	UPROPERTY(EditAnywhere, Category = Spawn)
		TSubclassOf<AActor_GhostTail> SpawnGhostClass;

	void SpawnGhostTail();


	// *** skill // ***
	

	// *** item ***
	
		// 힐링
	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* Healing_AnimMontage;

	void UseHealingItem();

	void SetItemCount_Heal(int32 itemCount);

		// 강화
	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* Reinforce_AnimMontage;

	UPROPERTY(EditAnywhere, Category = Skill)
		TArray<TSubclassOf<class AActor>> Array_ReinforceEffectClass;
	
	UPROPERTY(EditAnywhere, Category = Skill)
		class AActor* ReinforceEffect;

	void SpwnReinforceAura();

	void EndReinforce();

	void ApplyReinforce();

	void SetItemCount_Reinforce(int32 itemCount);

	
	// Buff
	virtual void ApplyBuff_Heart() override;

	virtual void ApplyBuff_Energy() override;

	virtual void ApplyBuff_Arcane() override;

	virtual void ApplyBuff_Dia() override;

	virtual void ApplyBuff_Shield() override;

	virtual void ResetBuff() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// *** Controlling
	UFUNCTION()
		void MoveForward(float Axisval);
	UFUNCTION()
		void MoveRight(float Axisval);
	
	virtual void AddControllerPitchInput(float Axisval);
	virtual void AddControllerYawInput(float Axisval);
	virtual void Landed(const FHitResult& Hit) override;
		
	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();
	

	UFUNCTION()
		void PressDash();

	UFUNCTION()
		void Attack_0();

	UFUNCTION()
		void Disarm();

	

	UPROPERTY(VisibleAnywhere)
	int32 jumpCount = 0;

	int32 ComboAttackNum = 1;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* TPSCameraComponent;

	

	UPROPERTY(EditAnywhere, Category = Anim)
		UAnimMontage* DoubleJump_AnimMontage;
	
	

	void SetGroundFriction(float friction);
	void ResetGroundFriction();

	UFUNCTION()
		void HpUIAplly();

	UFUNCTION()
		void TakeDamageAplly(float _damage);


	void InputSkill_Q();

	void InputSkill_E();

	void InputItem_1();

	void InputItem_2();

	// 상호작용 
	void InputInterection();
	FOnInteraction_Delegate OnInteraction;

	


private:

	class ATPSPlayerController* playerController;

	// 스킬
	float current_CooTime_Q;
	float Def_CooTime_Q;
	bool coolDown_Q;

	float current_CooTime_E;
	float Def_CooTime_E;
	bool coolDown_E;

	float current_CooTime_1;
	float Def_CooTime_1;
	bool coolDown_1;

	float current_CooTime_2;
	float Def_CooTime_2;
	bool coolDown_2;

	int32 SchoolCode;

	int32 CurrentItemCount_Heal;
	int32 MaxItemCount_Heal = 2;

	float ReinforceDuration = 30.0f;
	float CurrentReinforceTime = 0.0;
	bool bReinforce = false;

	int32 CurrentCount_Reinforce;
	int32 MaxCount_Reinforce = 1;

};
