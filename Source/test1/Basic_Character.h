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

	int32 MaxCombo;
	int32 currentCombo;


	virtual void OnHit(float InputDamage, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	//void TakeDamage();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DieCharacter();

	void DestroyCharacter();

	UPROPERTY(VisibleAnywhere, Category = Stat)
		class UCharacter_Stat_Component* Status_Component;
	

	void DefaultAttack();

	virtual void AttackEnd();
	
	void TakeShock();
	void EndShock();

	bool GetCheckShocking();
};
