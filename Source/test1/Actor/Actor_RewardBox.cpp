// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_RewardBox.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AActor_RewardBox::AActor_RewardBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InterectionBox"));
	RootComponent = InteractionCollision;

	InteractionCollision->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
}


void AActor_RewardBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	player = Cast<ATPS_Character>(OtherActor);
	if (player) {
		// 델리케이트 연결
		player->OnInteraction.Clear();
		player->OnInteraction.AddLambda([this]() -> void {
			OnIteraction.Broadcast();
			});

		auto plcontroller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (plcontroller) {
			plcontroller->OpenInteractionUI();
		}

	}
}

void AActor_RewardBox::NotifyActorEndOverlap(AActor* OtherActor)
{
	player = Cast<ATPS_Character>(OtherActor);
	if (player) {
		// 델리케이트 초기화
		player->OnInteraction.Clear();

		auto plcontroller = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (plcontroller) {
			plcontroller->CloseInteractionUI();
		}
	}
}


void AActor_RewardBox::SetBuff(int32 code)
{
	if (code >= BuffArray.Num()) return;

	// 버프 모델 생성
	FVector spwLoc = GetActorLocation();
	FRotator spwRot = GetActorRotation();
	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();
	ModelObj = world->SpawnActor<AActor>(BuffArray[code], spwLoc, spwRot, SpawnInfo);


	// OnIteraction 함수 연결
	switch (code)
	{
	case 0:
		OnIteraction.AddUObject(this, &AActor_RewardBox::GetHeart);
		break;
	case 1:
		OnIteraction.AddUObject(this, &AActor_RewardBox::GetEnergy);
		break;
	case 2:
		OnIteraction.AddUObject(this, &AActor_RewardBox::GetArcane);
		break;
	case 3:
		OnIteraction.AddUObject(this, &AActor_RewardBox::GetDia);
		break;
	case 4:
		OnIteraction.AddUObject(this, &AActor_RewardBox::GetShield);
		break;
	default:
		break;
	}

	// OnEndReward 함수 연결
	OnEndReward.AddLambda([this]()->void {
		if (ModelObj) {
			ModelObj->Destroy();
		};
		});
}


void AActor_RewardBox::GetHeart()
{
	if (player) {
		player->ApplyBuff_Heart();
		player->OnInteraction.Clear();
	}
	OnEndReward.Broadcast();
}

void AActor_RewardBox::GetEnergy()
{
	if (player) {
		player->ApplyBuff_Energy();
		player->OnInteraction.Clear();
	}
	OnEndReward.Broadcast();
}

void AActor_RewardBox::GetArcane()
{
	if (player) {
		player->ApplyBuff_Arcane();
		player->OnInteraction.Clear();
	}
	OnEndReward.Broadcast();
}

void AActor_RewardBox::GetDia()
{
	if (player) {
		player->ApplyBuff_Dia();
		player->OnInteraction.Clear();
	}
	OnEndReward.Broadcast();
}

void AActor_RewardBox::GetShield()
{
	if (player) {
		player->ApplyBuff_Shield();
		player->OnInteraction.Clear();
	}
	OnEndReward.Broadcast();
}

AActor* AActor_RewardBox::GetModel()
{
	return ModelObj;
}


