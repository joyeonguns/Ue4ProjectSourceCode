// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnCanNextComboDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackCollision_OnDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackCollision_OffDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHitStart_Delegate);
DECLARE_MULTICAST_DELEGATE(FOnApplySkill_Q_Delegate);
DECLARE_MULTICAST_DELEGATE(FOnHitEnd_Enemy_Delegate);
DECLARE_MULTICAST_DELEGATE(FOnUseItem_Delegate);
DECLARE_MULTICAST_DELEGATE(FOnEndHeal_Delegate);
DECLARE_MULTICAST_DELEGATE(FOnApplyReinforce_Delegate);
DECLARE_MULTICAST_DELEGATE(FOnEndMotion_Delegate);
DECLARE_MULTICAST_DELEGATE(FOnDashSlash_Delegate);
DECLARE_MULTICAST_DELEGATE(FOnSpawnGhost_Delegate);

UCLASS()
class TEST1_API UTPSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTPSAnimInstance();
	// 프래임당 실행
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	FOnCanNextComboDelegate OnCanNextComboDelegate;
	FOnAttackEndDelegate OnAttackEndDelegate;
	FOnAttackCollision_OnDelegate OnAttackCollision_On;
	FOnAttackCollision_OffDelegate OnAttackCollision_Off;
	FOnHitStart_Delegate OnHitStart;
	FOnApplySkill_Q_Delegate OnApplySkill_Q_Delegate;
	FOnHitEnd_Enemy_Delegate OnHitEnd_Enemy_Delegate;
	FOnUseItem_Delegate OnUseItem_Delegate;
	FOnEndHeal_Delegate OnEndHeal_Delegate;
	FOnApplyReinforce_Delegate OnApplyReinforce_Delegate;
	FOnEndMotion_Delegate OnEndMotion_Delegate;
	FOnDashSlash_Delegate OnDashSlash_Delegate;
	FOnSpawnGhost_Delegate OnSpawnGhost_Delegate;

protected:


private:

	UFUNCTION()
		void AnimNotify_AttackEnd();

	UFUNCTION()
		void AnimNotify_CanNextCombo();

	UFUNCTION()
		void AnimNotify_Attack_On();

	UFUNCTION()
		void AnimNotify_Attack_End();

	UFUNCTION()
		void AnimNotify_hitStart();

	UFUNCTION()
		void AnimNotify_ApplySkill_Q();

	UFUNCTION()
		void AnimNotify_hitEnd();

	UFUNCTION()
		void AnimNotify_useItem();

	UFUNCTION()
		void AnimNotify_EndHeal();

	UFUNCTION()
		void AnimNotify_ApplyAura();

	UFUNCTION()
		void AnimNotify_EndMotion();

	UFUNCTION()
		void AnimNotify_Dash_Slash_Dash();

	UFUNCTION()
		void AnimNotify_SpawnGhost();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
		float CurrentPawnSpeed;


};
