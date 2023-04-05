// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_SpawnSkill_Q.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AActor_SpawnSkill_Q::AActor_SpawnSkill_Q()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AActor_SpawnSkill_Q::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	if (OtherActor->IsA(AActor::StaticClass()) && OtherActor->ActorHasTag("Player") == false) {
		UGameplayStatics::ApplyDamage(OtherActor, 50, NULL, myOwner, UDamageType::StaticClass());
		auto target = Cast<ABasic_Character>(OtherActor);
		
		// 디버프 적용
		if (target) {
			if (School == "fire") {
				target->GetDeBuff_Burn();
			}
			else if (School == "volt") {
				target->GetDeBuff_Electric();
			}
			else if (School == "aqua") {
				target->GetDeBuff_Wet();
			}
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Skill"));
	}
}


void AActor_SpawnSkill_Q::SetOwner(ATPS_Character* _myOwner)
{
	myOwner = _myOwner;
}

void AActor_SpawnSkill_Q::SetDamage(float _damage)
{
	Damage = _damage;
}

