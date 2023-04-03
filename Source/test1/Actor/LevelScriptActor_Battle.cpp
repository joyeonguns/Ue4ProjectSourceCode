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
		SpawnComment(currentStage);

		FTimerHandle th;
		GetWorldTimerManager().SetTimer(th, this, &ALevelScriptActor_Battle::StageStart, 3.0f, false);
	}
	else {
		
	}

	
}

void ALevelScriptActor_Battle::StageStart()
{
	DeleteComment();


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

	live_StageEnemy = RangeEnemyCount + MeleeEnemyCount + BossEnemyCount;
	SpawnEnemy();

	bliveStage = true;
	/*switch (currentStage)
	{
	case 1:		
		RangeEnemyCount = 1;
		MeleeEnemyCount = 0;
		BossEnemyCount = 0;
		live_StageEnemy = RangeEnemyCount + MeleeEnemyCount + BossEnemyCount;
		SpawnEnemy();
		break;

	case 2:
		RangeEnemyCount = 3;
		MeleeEnemyCount = 2;
		BossEnemyCount = 0;
		live_StageEnemy = RangeEnemyCount + MeleeEnemyCount + BossEnemyCount;
		SpawnEnemy();
		break;

	case 3:
		RangeEnemyCount = 5;
		MeleeEnemyCount = 3;
		BossEnemyCount = 0;
		live_StageEnemy = RangeEnemyCount + MeleeEnemyCount + BossEnemyCount;
		SpawnEnemy();
		break;

	default:
		live_StageEnemy = 100;
		break;
	}*/
}

void ALevelScriptActor_Battle::SpawnEnemy()
{
	int level = 0;
	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		level = _GameInstance->statusArray[4];
	}
	

	for (int i = 0; i < MeleeEnemyCount; i++) {
		
		FVector SpwLoc = MeleeSpwLoc + FVector(0, -300, 0) * i;
		FRotator SpwRot = RewardSpwRot;;
		FActorSpawnParameters SpawnInfo;
		UWorld* world = GetWorld();
		auto melee = world->SpawnActor<AEnemyMelee_Character>(MeleeEnemyClass, SpwLoc, SpwRot, SpawnInfo);

		if (melee) {
			melee->OnDeadDelegate.AddUObject(this, &ALevelScriptActor_Battle::EnemySignal);
			melee->SetPrize(melee->GetPrize() + level);

			int32 rand = FMath::RandRange(0, 9);
			if (rand < EnemyBuffPercent) {
				melee->SetPrize(melee->GetPrize() * 2);
				// 버프
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

	for (int i = 0; i < RangeEnemyCount; i++) {

		FVector SpwLoc = RangeSpwLoc + FVector(-300, 0, 0) * i;
		FRotator SpwRot = RewardSpwRot;;
		FActorSpawnParameters SpawnInfo;
		UWorld* world = GetWorld();
		auto range = world->SpawnActor<AEnemyRange_Character>(RangeEnemyClass, SpwLoc, SpwRot, SpawnInfo);

		if (range) {
			range->OnDeadDelegate.AddUObject(this, &ALevelScriptActor_Battle::EnemySignal);
			range->SetPrize(range->GetPrize() + level);

			int32 rand = FMath::RandRange(0, 9);
			if (EnemyBuffPercent) {
				// 버프
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
	live_StageEnemy--;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Enemy : ")) + FString::FormatAsNumber(live_StageEnemy));

	if (live_StageEnemy <= 0 && bliveStage) {
		live_StageEnemy = 0;
		bliveStage = false;
		StageClear();
	}
}


void ALevelScriptActor_Battle::StageClear()
{
	if (currentStage < 5) {
		auto player = Cast<ATPS_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player) {
			player->ResetBuff();
		}



		SpawnRewardBox();

		// Reward 생성
		SpawnComment();
	}
	else {
		// UI 출력
		if (!RewardwidgetInstance) {
			RewardwidgetInstance = CreateWidget<UUserWidget_LevelText>(GetWorld(), RewardwidgetClass);
		}

		if (RewardwidgetInstance) {
			RewardwidgetInstance->SetComments_GameClear();
			RewardwidgetInstance->AddToViewport();
		}
	}
	
}

void ALevelScriptActor_Battle::SpawnRewardBox()
{
	SetBuffCode();

	FVector spwLoc = RewardSpwLoc;
	FRotator spwRot = RewardSpwRot;
	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();
	leftReward = world->SpawnActor<AActor_RewardBox>(RewardBoxClass, spwLoc, spwRot, SpawnInfo);

	rightReward = world->SpawnActor<AActor_RewardBox>(RewardBoxClass, spwLoc + FVector(300, 0, 0), spwRot, SpawnInfo);


	if (leftReward && rightReward) {
		leftReward->SetBuff(BuffCode_left);
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
	TArray<int32> MyArray;

	// populate the array with some values
	MyArray.Add(0);
	MyArray.Add(1);
	MyArray.Add(2);
	MyArray.Add(3);
	MyArray.Add(4);

	// shuffle the array using the FMath::RandRange function
	for (int32 Index = 0; Index < MyArray.Num(); Index++)
	{
		const int32 RandomIndex = FMath::RandRange(0, MyArray.Num() - 1);
		MyArray.Swap(Index, RandomIndex);
	}

	BuffCode_right = MyArray[0];
	BuffCode_left = MyArray[1];
}

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

void ALevelScriptActor_Battle::CheckStage()
{

}

void ALevelScriptActor_Battle::GetReWard(int32 itemCode)
{
	DeleteComment();

	// Ui 출력
	if (RewardwidgetInstance) {
		RewardwidgetInstance->RemoveFromParent();
	}

	FTimerHandle th;
	GetWorldTimerManager().SetTimer(th, this, &ALevelScriptActor_Battle::BeforeStage, 5.0f, false);

}

void ALevelScriptActor_Battle::GetReWard()
{
	GetReWard(5);
}

