// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMelee_Character.h"
#include "Enemy_AIController.h"

AEnemyMelee_Character::AEnemyMelee_Character()
{
	/*PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemy_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Set_HpBar();

	bOnHpBar = false;
	lifeTime_HpBar = 0.0f;
	AttackRange = 150.f;
	AttackRadius = 50.0f;*/


	
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
				HitResult.Actor->TakeDamage(10.0f, DamageEvent, GetController(), this);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HIT!!!"));
			}
		}
	}
}


void AEnemyMelee_Character::Attack()
{
	Super::Attack();
	PlayAnimMontage(DefaultAttack_Montage);
}

void AEnemyMelee_Character::AttackEnd()
{
	Super::AttackEnd();
	OnAttackEnd.Broadcast();
}

