// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRange_Character.h"
#include "Enemy_AIController.h"

AEnemyRange_Character::AEnemyRange_Character()
{
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

		Anim->OnAttackCollision_On.AddUObject(this, &AEnemyRange_Character::AttackCheck);

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

//	FHitResult HitResult;
//	FCollisionQueryParams Param(NAME_None, false, this);
//	bool bResult = GetWorld()->SweepSingleByChannel(
//		HitResult,
//		GetActorLocation(),
//		GetActorLocation() + GetActorForwardVector() * 150.f,
//		FQuat::Identity,
//		ECollisionChannel::ECC_GameTraceChannel2,
//		FCollisionShape::MakeSphere(50.0f),
//		Param
//	);
//
//
//#if ENABLE_DRAW_DEBUG
//
//	FVector TraceVec = GetActorForwardVector() * AttackRange;
//	FVector Center = GetActorLocation() + TraceVec * 0.5f;
//	float HalfHeight = AttackRange * 0.5f + AttackRadius;
//	FQuat CapsulRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
//	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
//	float DebugLife = 1.0f;
//
//	DrawDebugCapsule(GetWorld(),
//		Center,
//		HalfHeight,
//		AttackRadius,
//		CapsulRot,
//		DrawColor,
//		false,
//		DebugLife
//	);
//
//
//#endif // ENABLE_DRAW_DEBUG
//
//
//	if (bResult) {
//		if (HitResult.Actor.IsValid()) {
//			if (HitResult.Actor->ActorHasTag("Player")) {
//				FDamageEvent DamageEvent;
//				HitResult.Actor->TakeDamage(10.0f, DamageEvent, GetController(), this);
//				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HIT!!!"));
//			}
//		}
//	}
}

void AEnemyRange_Character::SpwArrow()
{
	// 화살 스폰
	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();
	arrowInstance = world->SpawnActor<ASPWArrow_Actor>(SpwArrowClass, SpawnInfo);

	if (arrowInstance) {
		arrowInstance->SetOwner(this);
		
		arrowInstance->Attaching(AttachName);	

	}
}

USkeletalMeshComponent* AEnemyRange_Character::GetSpecificPawnMesh() const
{
	return GetMesh();;
}

void AEnemyRange_Character::Shutting()
{
	if (arrowInstance) {
		auto ai = Cast<AEnemy_AIController>(GetController());
		if (ai) {
			arrowInstance->SetTargetLocation(ai->GetPlayer()->GetActorLocation());
		}
		arrowInstance->Shutting();
		arrowInstance->bIsShutt = true;
	}

}

void AEnemyRange_Character::DropArrow()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DropArrow"));
	arrowInstance->Destroy();
}

void AEnemyRange_Character::Attack()
{
	Super::Attack();
	PlayAnimMontage(DefaultAttack_Montage);
	SpwArrow();

	/*FTimerHandle TH;
	GetWorldTimerManager().SetTimer(TH, this, &AEnemyRange_Character::Shutting, 2.7f, false);*/
}

void AEnemyRange_Character::AttackEnd()
{
	Super::AttackEnd();
	OnAttackEnd.Broadcast();

	Shutting();
}

