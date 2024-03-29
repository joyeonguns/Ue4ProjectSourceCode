﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRange_Character.h"
#include "Enemy_AIController.h"

AEnemyRange_Character::AEnemyRange_Character()
{
	realMoveSpeed = DefaultWalkSpeed;
	Status_Component->SetMode(2);
}


void AEnemyRange_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Anim = Cast<UTPSAnimInstance>(GetMesh()->GetAnimInstance());

	if (Anim) {
		Anim->OnAttackCollision_Off.AddLambda([this]() -> void {
			UE_LOG(LogTemp, Warning, TEXT("OnAttackCollision_Off"));
			AttackEnd();
			});

		Anim->OnAttackCollision_On.AddUObject(this, &AEnemyRange_Character::SpwArrow);

		Anim->OnHitStart.AddUObject(this, &AEnemyRange_Character::DropArrow);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Anim_Enemy_Error"));
	}

	// 투사체 발사
}

void AEnemyRange_Character::BeginPlay()
{
	Super::BeginPlay();
	AttackRange = 1800.f;
	AttackRadius = 50.0f;
}

void AEnemyRange_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AEnemyRange_Character::AttackCheck()
{
	Super::AttackCheck();

}

void AEnemyRange_Character::SpwArrow()
{
	// 화살 스폰
	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();
	arrowInstance = world->SpawnActor<ASPWArrow_Actor>(SpwArrowClass, SpawnInfo);

	if (arrowInstance) {
		arrowInstance->SetDamage(Status_Component->Getcurrent_Status()->Damage);

		// 특성 적용
		int32 percent = Status_Component->Getcurrent_Status()->percentage;
		int32 rnd = FMath::RandRange(0, 99);
		if (rnd < percent) arrowInstance->SetDamage(Status_Component->Getcurrent_Status()->Damage * 2);

		// 오너 세팅
		arrowInstance->SetOwner(this);
		// 화살 부착
		arrowInstance->Attaching(AttachName);	

		// 타겟 세팅
		auto ai = Cast<AEnemy_AIController>(GetController());
		if (ai) {
			arrowInstance->SetTargetPawn(ai->GetPlayer());
		}
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("!SpwArrow"));
	}
}

USkeletalMeshComponent* AEnemyRange_Character::GetSpecificPawnMesh() const
{
	return GetMesh();;
}

void AEnemyRange_Character::Shutting()
{
	if (arrowInstance) {		
		arrowInstance->Shootting();
		arrowInstance->bIsShutt = true;
		arrowInstance = nullptr;
	}

}

void AEnemyRange_Character::DropArrow()
{
	// 공격 받을시 화살제거
	if (arrowInstance) {
		arrowInstance->Destroy();
		arrowInstance = nullptr;
	}	
}

float AEnemyRange_Character::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DropArrow();
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return Damage;
}

void AEnemyRange_Character::Attack()
{
	Super::Attack();
	if (bAttacking == false && !bShocking) {
		PlayAnimMontage(DefaultAttack_Montage, Attack_Speed);
		bAttacking = true;
	}
	
}

void AEnemyRange_Character::AttackEnd()
{
	Super::AttackEnd();

	Shutting();
	bAttacking = false;
}

