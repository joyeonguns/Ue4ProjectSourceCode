// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "EnemyMelee_Character.h"
#include "EnemyRange_Character.h"
#include "Blueprint/UserWidget.h"
#include "Actor_RewardBox.h"
#include "UserWidget_LevelText.h"
#include "LevelScriptActor_Battle.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API ALevelScriptActor_Battle : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	ALevelScriptActor_Battle();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;


	void BeforeStage();

	void StageStart();

	void CheckStage();

	void StageClear();

	void GetReWard(int32 itemCode);

	void GetReWard();

	void SpawnEnemy();

	void EnemySignal();

	void SpawnRewardBox();

	void SetBuffCode();

	void SpawnComment(int32 stage);
	void SpawnComment();
	void DeleteComment();


private:
	int32 currentStage;

	int32 RangeEnemyCount;
	int32 MeleeEnemyCount;
	int32 BossEnemyCount;
	int32 live_StageEnemy;

	int32 BuffCode_right = 0;
	int32 BuffCode_left = 0;

	int32 EnemyBuffPercent = 0;
	
	bool bliveStage;

	// 스폰 위치
	UPROPERTY(EditAnywhere, Category = SpW)
		FVector RangeSpwLoc;
	UPROPERTY(EditAnywhere, Category = SpW)
		FVector MeleeSpwLoc;
	UPROPERTY(EditAnywhere, Category = SpW)
		FVector BossSpwLoc;
	UPROPERTY(EditAnywhere, Category = SpW)
		FVector RewardSpwLoc;
	UPROPERTY(EditAnywhere, Category = SpW)
		FRotator RewardSpwRot;

	// 적 스폰 클래스
	UPROPERTY(EditAnywhere, Category = SpW)
		TSubclassOf<class AEnemyMelee_Character> MeleeEnemyClass;

	UPROPERTY(EditAnywhere, Category = SpW)
		TSubclassOf<class AEnemyRange_Character> RangeEnemyClass;

	// 보상 상자
	UPROPERTY(EditAnywhere, Category = SpW)
		TSubclassOf<class AActor_RewardBox> RewardBoxClass;

	class AActor_RewardBox* leftReward;
	class AActor_RewardBox* rightReward;


	// Before Stage UI

	// Clear Stage UI

	// 보상 UI
	UPROPERTY(EditAnywhere, Category = UI)
		TSubclassOf<class UUserWidget_LevelText> RewardwidgetClass;

	UPROPERTY(EditAnywhere, Category = UI)
		class UUserWidget_LevelText* RewardwidgetInstance;
	


};
