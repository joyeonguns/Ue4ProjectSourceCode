// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMelee_Character.h"
#include "Enemy_AIController.h"

AEnemyMelee_Character::AEnemyMelee_Character()
{	
	realMoveSpeed = DefaultRunSpeed;
	Status_Component->SetMode(1);
}

void AEnemyMelee_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Anim = Cast<UTPSAnimInstance>(GetMesh()->GetAnimInstance());

	if (Anim) {
		Anim->OnAttackCollision_Off.AddLambda([this]() -> void {
			UE_LOG(LogTemp, Warning, TEXT("OnAttackCollision_Off"));
			AttackEnd();
			});

		Anim->OnAttackCollision_On.AddUObject(this, &AEnemyBasic_Character::AttackCheck);

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Anim_Enemy_Error"));
	}

	
}

void AEnemyMelee_Character::BeginPlay()
{
	Super::BeginPlay();
	AttackRange = 150.f;
	AttackRadius = 50.0f;
}

void AEnemyMelee_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyMelee_Character::AttackCheck()
{
	Super::AttackCheck();

	FHitResult HitResult;
	FCollisionQueryParams Param(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 150.f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Param
	);


#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsulRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLife = 1.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsulRot,
		DrawColor,
		false,
		DebugLife
	);


#endif // ENABLE_DRAW_DEBUG


	if (bResult) {
		if (HitResult.Actor.IsValid()) {
			if (HitResult.Actor->ActorHasTag("Player")) {
				FDamageEvent DamageEvent;
				float Damage = Status_Component->Getcurrent_Status()->Damage;

				int32 percent = Status_Component->Getcurrent_Status()->percentage;
				int32 rnd = FMath::RandRange(0, 99);
				if (rnd < percent) Damage *= 2;


				HitResult.Actor->TakeDamage(Damage, DamageEvent, GetController(), this);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HIT!!!"));
			}
		}
	}
}


void AEnemyMelee_Character::Attack()
{
	Super::Attack();
	if (bAttacking == false && !bShocking) {
		PlayAnimMontage(DefaultAttack_Montage, Attack_Speed);
		bAttacking = true;
	}
	
}

void AEnemyMelee_Character::AttackEnd()
{
	Super::AttackEnd();
	bAttacking = false;
}

