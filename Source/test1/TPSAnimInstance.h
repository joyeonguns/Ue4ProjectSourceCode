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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
		float CurrentPawnSpeed;


};
