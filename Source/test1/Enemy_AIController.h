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

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	float AISightRadius = 500.0f;
	float AISightAge = 5.f;
	float AILoseSightRadius = AISightRadius + 100.0f;
	float AIFieldOfView = 90.0f;
	class UAISenseConfig_Sight* SightConfig;


	class ATPS_Character* GetPlayer();

	UFUNCTION()
		void OnDetected(const TArray<AActor*> &DetectedActor);

protected:


private:
	void OnRepeatTimer();

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
