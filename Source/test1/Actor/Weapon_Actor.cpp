// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon_Actor::AWeapon_Actor(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 매쉬 생성
	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Weapon_Mesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	// 컬리전 생성
	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon_Collision"));
	WeaponCollision->SetBoxExtent(FVector(3.f, 3.f, 3.f));
	WeaponCollision->AttachTo(WeaponMesh, "DamageSoket");
}

void AWeapon_Actor::SetOwningPawn(class ATPS_Character* WeaponOwner)
{	
	if (MyOwner != WeaponOwner) {
		MyOwner = WeaponOwner;
	}
}

void AWeapon_Actor::AttachMeshToPawn(FName AttachName)
{
	// 무기를 부착
	if (MyOwner) {
		USkeletalMeshComponent* PawnMessh = MyOwner->GetSpecificPawnMesh();
		//FName AttackPoint = MyOwner->GetWeaponAttachPoint();
		WeaponMesh->AttachTo(PawnMessh, AttachName);
	}
}

void AWeapon_Actor::OnEquip(const AWeapon_Actor* LastWeapon)
{
	//AttachMeshToPawn();
}

void AWeapon_Actor::ApplyAttack()
{
	// 0.3초후 컬리전 적용
	FTimerHandle TH_Attack_Apply;
	GetWorldTimerManager().SetTimer(TH_Attack_Apply, this, &AWeapon_Actor::ApplyCollision, 0.3f, false);

	// 0.7초 후 컬리전 해제
	FTimerHandle TH_Attack0_End;
	GetWorldTimerManager().SetTimer(TH_Attack0_End, this, &AWeapon_Actor::DeleteCollision, 0.7f, false);
}

void AWeapon_Actor::ApplyCollision()
{
	WeaponCollision->SetGenerateOverlapEvents(true);

	// 주기적으로 잔상 생성 
	GetWorldTimerManager().SetTimer(TH_Ghost, this, &AWeapon_Actor::SpawnGhostTail,  0.01f, true);
}

void AWeapon_Actor::DeleteCollision()
{
	WeaponCollision->SetGenerateOverlapEvents(false);

	// 잔상 생성 해제
	GetWorldTimerManager().ClearTimer(TH_Ghost);
}

void AWeapon_Actor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AActor::StaticClass()) && OtherActor->ActorHasTag("Player") == false) {
		float damage;
		bool bDebuff = false;

		// 데미지 계산
		damage = MyOwner->Status_Component->GetStatus()->Damage;
		

		// 디버프 적용
		FString School = MyOwner->Status_Component->Getcurrent_Status()->School;
		int32 percent = MyOwner->Status_Component->Getcurrent_Status()->percentage;


		int32 rnd = FMath::RandRange(0, 99);

		if (rnd < percent) bDebuff = true;
				
		
		auto Target = Cast<ABasic_Character>(OtherActor);
		if (!Target) return;

		if (Target->GetbDead()) return;

		if (Target && bDebuff) {
			if (School == "fire") {
				Target->GetDeBuff_Burn();
			}
			else if (School == "volt") {
				Target->GetDeBuff_Electric();
			}
			else if (School == "aqua") {
				Target->GetDeBuff_Wet();
			}
			else {
				damage *= 2;
			}		
		}

		// 데미지 적용
		UGameplayStatics::ApplyDamage(OtherActor, damage, NULL, MyOwner, UDamageType::StaticClass());

	}
}

void AWeapon_Actor::SpawnGhostTail()
{
	// 잔상 생성
	FVector spwLoc = GetActorLocation() ;
	FRotator spwRot = GetActorRotation() ;
	FActorSpawnParameters spwInfo;


	auto GhostTailInstance = GetWorld()->SpawnActor<AActor_GhostTail>(SpawnGhostClass, spwLoc, spwRot, spwInfo);
	if (GhostTailInstance) {
		GhostTailInstance->Init(WeaponMesh);
	}
	
}



