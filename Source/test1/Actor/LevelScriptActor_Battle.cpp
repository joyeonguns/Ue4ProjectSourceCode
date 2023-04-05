// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelScriptActor_Battle.h"
#include "Kismet/GameplayStatics.h"
#include "TPSGameInstance.h"

ALevelScriptActor_Battle::ALevelScriptActor_Battle()
{
	RangeSpwLoc = FVector(-2500, -2500, 2100);
	MeleeSpwLoc = FVector(-2500, -1500, 2100);;
}

void ALevelScriptActor_Battle::BeginPlay()
{
	Super::BeginPlay();
	BeforeStage();

	// 적 버프 획득 확률 가져오기
	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	EnemyBuffPercent = _GameInstance->statusArray[5];

}

void ALevelScriptActor_Battle::Tick(float DeltaTime)
{
}

void ALevelScriptActor_Battle::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ALevelScriptActor_Battle::BeforeStage()
{	
	//StageClear();
	currentStage++;
	// BeforeStage UI 생성
	DeleteComment();


	if (currentStage <= 5) {
		// UI 생성
		SpawnComment(currentStage);

		// 3초후 StageStart 함수 호출
		FTimerHandle th;
		GetWorldTimerManager().SetTimer(th, this, &ALevelScriptActor_Battle::StageStart, 3.0f, false);
	}
}

void ALevelScriptActor_Battle::StageStart()
{
	// UI 제거
	DeleteComment();

	// 적 스테이지 맞는 스폰 데이터 저장
	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		_GameInstance->BattleData_Enemy->Melee = _GameInstance->Get_FStageDataTable(currentStage)->Melee;
		_GameInstance->BattleData_Enemy->Range = _GameInstance->Get_FStageDataTable(currentStage)->Range;
		_GameInstance->BattleData_Enemy->Boss = _GameInstance->Get_FStageDataTable(currentStage)->Boss;
		_GameInstance->BattleData_Enemy->Stage = currentStage;

		RangeEnemyCount = _GameInstance->BattleData_Enemy->Range;
		MeleeEnemyCount = _GameInstance->BattleData_Enemy->Melee;
		BossEnemyCount = _GameInstance->BattleData_Enemy->Boss;
	}

	// 살아있는 적 초기화
	live_StageEnemy = RangeEnemyCount + MeleeEnemyCount + BossEnemyCount;
	
	// 적 생성
	SpawnEnemy();

	bliveStage = true;
}

void ALevelScriptActor_Battle::SpawnEnemy()
{
	// 적 레벨 가져오기
	int level = 0;
	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		level = _GameInstance->statusArray[4];
	}
	
	// 근거리 적 소환
	for (int i = 0; i < MeleeEnemyCount; i++) {
		
		FVector SpwLoc = MeleeSpwLoc + FVector(0, -300, 0) * i;
		FRotator SpwRot = RewardSpwRot;;
		FActorSpawnParameters SpawnInfo;
		UWorld* world = GetWorld();
		auto melee = world->SpawnActor<AEnemyMelee_Character>(MeleeEnemyClass, SpwLoc, SpwRot, SpawnInfo);

		if (melee) {
			// OnDeadDelegate에 EnemySignal 연결
			melee->OnDeadDelegate.AddUObject(this, &ALevelScriptActor_Battle::EnemySignal);
			melee->SetPrize(melee->GetPrize() + level);

			// 버프 적용
			int32 rand = FMath::RandRange(0, 9);
			if (rand < EnemyBuffPercent) {
				melee->SetPrize(melee->GetPrize() * 2);
				
				int32 randBuff = FMath::RandRange(1, 5);
				switch (randBuff)
				{
				case 1:
					melee->ApplyBuff_Arcane();
					break;
				case 2:
					melee->ApplyBuff_Dia();
					break;
				case 3:
					melee->ApplyBuff_Energy();
					break;
				case 4:
					melee->ApplyBuff_Heart();
					break;
				case 5:
					melee->ApplyBuff_Shield();
					break;
				default:
					break;
				}
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("!SpawnEnemy::melee"));
		}

		
	}


	// 원거리 적 소환
	for (int i = 0; i < RangeEnemyCount; i++) {

		FVector SpwLoc = RangeSpwLoc + FVector(-300, 0, 0) * i;
		FRotator SpwRot = RewardSpwRot;;
		FActorSpawnParameters SpawnInfo;
		UWorld* world = GetWorld();
		auto range = world->SpawnActor<AEnemyRange_Character>(RangeEnemyClass, SpwLoc, SpwRot, SpawnInfo);

		if (range) {
			// OnDeadDelegate에 EnemySignal 연결
			range->OnDeadDelegate.AddUObject(this, &ALevelScriptActor_Battle::EnemySignal);
			range->SetPrize(range->GetPrize() + level);

			// 버프
			int32 rand = FMath::RandRange(0, 9);
			if (EnemyBuffPercent) {
				range->SetPrize(range->GetPrize() * 2);
				int32 randBuff = FMath::RandRange(1, 5);
				switch (randBuff)
				{
				case 1:
					range->ApplyBuff_Arcane();
					break;
				case 2:
					range->ApplyBuff_Dia();
					break;
				case 3:
					range->ApplyBuff_Energy();
					break;
				case 4:
					range->ApplyBuff_Heart();
					break;
				case 5:
					range->ApplyBuff_Shield();
					break;
				default:
					break;
				}
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("!SpawnEnemy::range"));
		}
	}

	
}

void ALevelScriptActor_Battle::EnemySignal()
{
	// 적 죽을시 호출되는 함수
	live_StageEnemy--;

	// 스테이지 클리어 체크
	if (live_StageEnemy <= 0 && bliveStage) {
		live_StageEnemy = 0;
		bliveStage = false;
		StageClear();
	}
}


void ALevelScriptActor_Battle::StageClear()
{
	// 보상 생성
	if (currentStage < 5) {
		auto player = Cast<ATPS_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player) {
			player->ResetBuff();
		}

		// Reward 생성
		SpawnRewardBox();

		// Reward UI 생성
		SpawnComment();
	}
	// 게임 클리어
	else {
		// UI 출력
		if (!RewardwidgetInstance) {
			RewardwidgetInstance = CreateWidget<UUserWidget_LevelText>(GetWorld(), RewardwidgetClass);
		}
		else if (RewardwidgetInstance) {
			RewardwidgetInstance->SetComments_GameClear();
			RewardwidgetInstance->AddToViewport();
		}
	}
	
}

void ALevelScriptActor_Battle::SpawnRewardBox()
{
	// 버프 설정
	SetBuffCode();

	// 보상 상자 생성
	FVector spwLoc = RewardSpwLoc;
	FRotator spwRot = RewardSpwRot;
	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();
	leftReward = world->SpawnActor<AActor_RewardBox>(RewardBoxClass, spwLoc, spwRot, SpawnInfo);

	rightReward = world->SpawnActor<AActor_RewardBox>(RewardBoxClass, spwLoc + FVector(300, 0, 0), spwRot, SpawnInfo);


	if (leftReward && rightReward) {
		leftReward->SetBuff(BuffCode_left);
		// OnEndReward 함수 초기화
		leftReward->OnEndReward.AddLambda([this]()-> void {

			GetReWard(BuffCode_left);
			if (leftReward && rightReward) {
				leftReward->Destroy();
				rightReward->GetModel()->Destroy();
				rightReward->Destroy();
			}
			});

		rightReward->SetBuff(BuffCode_right);
		rightReward->OnEndReward.AddLambda([this]()-> void {

			GetReWard(BuffCode_right);
			if (leftReward && rightReward) {
				leftReward->GetModel()->Destroy();
				leftReward->Destroy();
				rightReward->Destroy();
			}
			});
	}
}

void ALevelScriptActor_Battle::SetBuffCode()
{
	// 겹치지 않는 랜덤 코드 2개 생성 
	TArray<int32> MyArray;

	MyArray.Add(0);
	MyArray.Add(1);
	MyArray.Add(2);
	MyArray.Add(3);
	MyArray.Add(4);

	// FMath::RandRange 배열 셔플
	for (int32 Index = 0; Index < MyArray.Num(); Index++)
	{
		const int32 RandomIndex = FMath::RandRange(0, MyArray.Num() - 1);
		MyArray.Swap(Index, RandomIndex);
	}

	// 버프 코드 할당
	BuffCode_right = MyArray[0];
	BuffCode_left = MyArray[1];
}


// *** UI 생성
void ALevelScriptActor_Battle::SpawnComment(int32 stage)
{
	// UI 출력
	if (!RewardwidgetInstance) {
		RewardwidgetInstance = CreateWidget<UUserWidget_LevelText>(GetWorld(), RewardwidgetClass);
	}

	if (RewardwidgetInstance) {
		RewardwidgetInstance->SetComments_StartStage(stage);
		RewardwidgetInstance->AddToViewport();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("!SpawnEnemy UI"));
}

void ALevelScriptActor_Battle::SpawnComment()
{
	// UI 출력
	if (!RewardwidgetInstance) {
		RewardwidgetInstance = CreateWidget<UUserWidget_LevelText>(GetWorld(), RewardwidgetClass);
	}

	if (RewardwidgetInstance) {
		RewardwidgetInstance->SetComments_Reward();
		RewardwidgetInstance->AddToViewport();
	}
}

void ALevelScriptActor_Battle::DeleteComment()
{
	if (RewardwidgetInstance) {
		RewardwidgetInstance->RemoveFromParent();
		RewardwidgetInstance = nullptr;
	}
}
// ** UI

void ALevelScriptActor_Battle::GetReWard(int32 itemCode)
{
	// Ui 제거
	DeleteComment();

	FTimerHandle th;
	GetWorldTimerManager().SetTimer(th, this, &ALevelScriptActor_Battle::BeforeStage, 5.0f, false);

}


