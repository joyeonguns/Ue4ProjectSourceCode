// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStat_DataTable.h"
#include "DataTable_StatLevel.h"
#include "Character_Stat_Component.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPApllyDelegate);
DECLARE_MULTICAST_DELEGATE(FOnTakeDamageDelegate);
DECLARE_MULTICAST_DELEGATE(FOnResetAuraDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTakeDamageDelegate_Param, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST1_API UCharacter_Stat_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacter_Stat_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	
public:
	// 게임 인스턴스의 데이터 가져오기
	void TakeInstanceDatas(int32 Rolecode);
	// current_Status 에 플레이어 캐릭터 정보 저장
	void SetCurrentData();

	// 데미지 설정
	void SetDamage(float Damage);	
	// 디버프로인한 데미지 설정
	void SetDebuffDamage(float Damage);
	// 캐릭터의 HP 설정
	void SetHp(float newHp);

	// 캐릭터 HP 고정 수치 회복
	void SetRecovery(float addHp);
	// 캐릭터 HP 비율 회복
	void SetRecovery_Percent(float addHp);

	// 현재 HP / 최대HP 
	float GetHpRatio();

	float GetHp();

	// HP == 0 일때 실행
	FOnHPIsZeroDelegate OnHpIsZero;
	// HP가 업데이트될때 실행
	FOnHPApllyDelegate OnHpApply;
	// 데미지를 받았을 시 실행
	FOnTakeDamageDelegate OnTakeDamage;
	// 오라를 제거
	FOnResetAuraDelegate OnResetAura;
	// 플레이어가 데미지를 받을시 실행
	FOnTakeDamageDelegate_Param OnTakeDamage_Param;

	// 모드 0 ==  플레이어, 0 != 적 캐릭터 
	void SetMode(int32 mode);

	FCharacterStat* GetStatus();

	// 캐릭터에 쉴드 버프 횟수 저장
	void SetShield(int32 NewShield);
	// 캐릭터의 목숨 저장
	void SetLife(int32 NewLife);

	struct FCharacterStat* Getcurrent_Status();

	// current_Status 에 적 캐릭터의 정보 저장
	void SetEnemyData();

private:

	// 플레이어 캐릭터 능력치 업그레이드
	struct FStatusLevel* current_StatusLevel = nullptr;
	// 캐릭터 기본 스테이터스 
	struct FCharacterStat* Default_Status = nullptr;
	// 캐릭터 현재 스테이터스
	struct FCharacterStat* current_Status = nullptr;
	

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		int32 code;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		FString School;
	UPROPERTY(Transient, EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
		float currentHp;

	UPROPERTY(EditAnywhere, Category = HUD)
		class UHUD_UserWidget* Hud;

	int32 Mode;

	int32 Shield = 0;
	int32 life = 0;

};
