// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon_Actor::AWeapon_Actor(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Weapon_Mesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

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
	
	FTimerHandle TH_Attack_Apply;
	GetWorldTimerManager().SetTimer(TH_Attack_Apply, this, &AWeapon_Actor::ApplyCollision, 0.3f, false);


	FTimerHandle TH_Attack0_End;
	GetWorldTimerManager().SetTimer(TH_Attack0_End, this, &AWeapon_Actor::DeleteCollision, 0.7f, false);
}

void AWeapon_Actor::ApplyCollision()
{
	WeaponCollision->SetGenerateOverlapEvents(true);
	GetWorldTimerManager().SetTimer(TH_Ghost, this, &AWeapon_Actor::SpawnGhostTail,  0.01f, true);
}

void AWeapon_Actor::DeleteCollision()
{
	WeaponCollision->SetGenerateOverlapEvents(false);
	GetWorldTimerManager().ClearTimer(TH_Ghost);
}

void AWeapon_Actor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AActor::StaticClass()) && OtherActor->ActorHasTag("Player") == false) {
		float damage;
		bool bDebuff = false;

		damage = MyOwner->Status_Component->GetStatus()->Damage;
		
		
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

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AWeapon_Actor::NotifyActorBeginOverlap:: !ApplyDebuff"));
		}

		UGameplayStatics::ApplyDamage(OtherActor, damage, NULL, MyOwner, UDamageType::StaticClass());

	}
}

void AWeapon_Actor::SpawnGhostTail()
{
	FVector spwLoc = GetActorLocation() ;
	FRotator spwRot = GetActorRotation() ;
	FActorSpawnParameters spwInfo;


	auto GhostTailInstance = GetWorld()->SpawnActor<AActor_GhostTail>(SpawnGhostClass, spwLoc, spwRot, spwInfo);
	if (GhostTailInstance) {
		GhostTailInstance->Init(WeaponMesh);
	}
	
}



