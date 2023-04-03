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

void UTPSAnimInstance::AnimNotify_ApplySkill_Q()
{
	OnApplySkill_Q_Delegate.Broadcast();
}

void UTPSAnimInstance::AnimNotify_hitEnd()
{
	OnHitEnd_Enemy_Delegate.Broadcast();
}

void UTPSAnimInstance::AnimNotify_useItem()
{
	OnUseItem_Delegate.Broadcast();
}

void UTPSAnimInstance::AnimNotify_EndHeal()
{
	OnEndHeal_Delegate.Broadcast();
}

void UTPSAnimInstance::AnimNotify_ApplyAura()
{
	OnApplyReinforce_Delegate.Broadcast();
}

void UTPSAnimInstance::AnimNotify_EndMotion()
{
	OnEndMotion_Delegate.Broadcast();
}

void UTPSAnimInstance::AnimNotify_Dash_Slash_Dash()
{
	OnDashSlash_Delegate.Broadcast();
}

void UTPSAnimInstance::AnimNotify_SpawnGhost()
{
	OnSpawnGhost_Delegate.Broadcast();
}

void UTPSAnimInstance::AnimNotify_AttackEnd()
{
	OnAttackEndDelegate.Broadcast();
}
