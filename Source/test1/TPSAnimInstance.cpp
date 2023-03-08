// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSAnimInstance.h"

UTPSAnimInstance::UTPSAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UTPSAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	auto Pawn = TryGetPawnOwner();
}

void UTPSAnimInstance::AnimNotify_CanNextCombo()
{
	OnCanNextComboDelegate.Broadcast();
}

void UTPSAnimInstance::AnimNotify_Attack_On()
{
	OnAttackCollision_On.Broadcast();
}

void UTPSAnimInstance::AnimNotify_Attack_End()
{
	OnAttackCollision_Off.Broadcast();
}

void UTPSAnimInstance::AnimNotify_hitStart()
{
	OnHitStart.Broadcast();
}

void UTPSAnimInstance::AnimNotify_AttackEnd()
{
	OnAttackEndDelegate.Broadcast();
}
