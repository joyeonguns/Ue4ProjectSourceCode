// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TPS_Character.h"
#include "Enemy_AIController.generated.h"

/**
 * 
 */
UCLASS()
class TEST1_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemy_AIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// 블랙보드 변수이름
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	static const FName TargetPosKey;
	static const FName bCanAttackKey;
	static const FName bShockKey;

	// AI Perception 데이터
	float AISightRadius = 500.0f;
	float AISightAge = 50.f;
	float AILoseSightRadius = AISightRadius + 100.0f;
	float AIFieldOfView = 90.0f;
	class UAISenseConfig_Sight* SightConfig;

	// Get 타겟
	class ATPS_Character* GetPlayer();
	

	UFUNCTION()
		void Setplayer(class ATPS_Character* _player);

	UFUNCTION()
		void OnDetected(const TArray<AActor*> &DetectedActor);


private:
	FTimerHandle ReapeatTimeHandler;
	float RepeatIntervar;

	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;

	UPROPERTY()
		class ATPS_Character* Player;

	
};
