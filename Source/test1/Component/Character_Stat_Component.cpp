// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Stat_Component.h"
#include "TPSGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TPSPlayerController.h"
#include "HUD_UserWidget.h"

// Sets default values for this component's properties
UCharacter_Stat_Component::UCharacter_Stat_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Inintialize 함수사용을 위해
	bWantsInitializeComponent = true;

	code = 2;
	// ...
}


// Called when the game starts
void UCharacter_Stat_Component::BeginPlay()
{
	Super::BeginPlay();
	// ...
		
}

void UCharacter_Stat_Component::InitializeComponent()
{
	Super::InitializeComponent();

	current_Status = new FCharacterStat();

	// 플레이어
	if (Mode == 0) {
		TakeInstanceDatas(code);
		SetCurrentData();
		SetHp(current_Status->Hp);
	}
	// 적
	else {
		current_Status = new FCharacterStat();
		SetEnemyData();
		SetHp(current_Status->Hp);
	}
}

void UCharacter_Stat_Component::TakeInstanceDatas(int32 Rolecode)
{

	// 게임 인스턴스의 정보를 가져옴
	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance Success"));
		
		// 특성코드 가져옴
		Rolecode = _GameInstance->SelectedSchoolCode;
		// 특성에 따른 플레이어 캐릭터 기본 정보저장
		Default_Status = _GameInstance->Get_FCharacter_Status(Rolecode);
		School = Default_Status->School;


		// 능력치 업그레이드 정보 저장
		if (_GameInstance->statusArray.Num() < 1) return;

		TArray<int32> _statusArray = _GameInstance->statusArray;


		current_StatusLevel = new FStatusLevel();
		current_StatusLevel->Hp = _GameInstance->Get_FStatusLevel(_statusArray[0])->Hp;
		current_StatusLevel->Damage = _GameInstance->Get_FStatusLevel(_statusArray[1])->Damage;
		current_StatusLevel->Critical = _GameInstance->Get_FStatusLevel(_statusArray[2])->Critical;
		current_StatusLevel->CoolTime = _GameInstance->Get_FStatusLevel(_statusArray[3])->CoolTime;

		_GameInstance->BattleData_Enemy->Level = _GameInstance->statusArray[4];
		_GameInstance->BattleData_Enemy->Elite = _GameInstance->statusArray[5] * 10;

		if (current_StatusLevel) {
			UE_LOG(LogTemp, Warning, TEXT("current_Status Success, School : %s"), *School);
			
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("current_Status ERROR"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance ERROR"));
	}

}

void UCharacter_Stat_Component::SetCurrentData()
{	
	// 캐릭터 기본 정보와 능력치 업그레이드를 통해 현재 캐릭터 정보 저장
	if (Default_Status == nullptr) return;

	current_Status->School = Default_Status->School;
	current_Status->Hp = Default_Status->Hp + current_StatusLevel->Hp;
	current_Status->Damage += Default_Status->Damage + current_StatusLevel->Damage;
	current_Status->Critical += Default_Status->Critical + current_StatusLevel->Critical;
	current_Status->CoolTime += Default_Status->CoolTime + current_StatusLevel->CoolTime;
	current_Status->percentage = Default_Status->percentage;

	currentHp = current_Status->Hp;

	// 게임 인스턴스의 전투 정보에 현재 캐릭터 정보 저장
	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		_GameInstance->BattleData_Player->Hp = current_Status->Hp;
		_GameInstance->BattleData_Player->Damage = current_Status->Damage;
		_GameInstance->BattleData_Player->Critical = current_Status->Critical;
		_GameInstance->BattleData_Player->Accel_CoolTime = current_Status->CoolTime;
		_GameInstance->BattleData_Player->Speed = 0;
		_GameInstance->BattleData_Player->School_Percent = current_Status->percentage;
	}	

	if (current_StatusLevel) {
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, School : %s"), *School);
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, Hp : %f"), current_Status->Hp);
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, Damage : %f"), current_Status->Damage);
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, Critical : %d"), current_Status->Critical);
		UE_LOG(LogTemp, Warning, TEXT("current_Status Success, CoolTime : %d"), current_Status->CoolTime);

	}
	
}

void UCharacter_Stat_Component::SetDamage(float Damage)
{
	// 쉴드가 있는 경우 쉴드 횟수만 감소
	if (Shield > 0) {
		Shield--;
		if (Shield == 0) {
			// 나음 쉴드 횟수가 없을 경우 오라 해제
			OnResetAura.Broadcast();
		}
		return;
	}
	// 쉴드가 없을 경우 데미지 적용
	else {
		Shield = 0;
		if (current_Status && currentHp > 0.0f) {
			// newHp 를 0 ~ 최대Hp 사이로 반환
			int newHp = FMath::Clamp<float>(currentHp - Damage, 0.0f, current_Status->Hp);
			// 데미지 수치 UI 생성 및 hit 애니메이션 실행 등 연결된 함수 실행
			OnTakeDamage.Broadcast();
			OnTakeDamage_Param.Broadcast(Damage);
			
			// newHp를 적용
			SetHp(newHp);
		}
	}	
}

void UCharacter_Stat_Component::SetDebuffDamage(float Damage)
{
	// 디버프 데미지는 쉴드의 영향을 받지 않음
	// 데미지 수치 UI 생성 X 및 hit 애니메이션 실행 X
	if (current_Status) {
		int newHp = FMath::Clamp<float>(currentHp - Damage, 0.0f, current_Status->Hp);
		SetHp(newHp);
	}
}

void UCharacter_Stat_Component::SetHp(float newHp)
{
	// 현재 Hp 저장
	currentHp = newHp;
	// Hp UI 업데이트
	OnHpApply.Broadcast();

	// HP <= 0
	if (currentHp <= KINDA_SMALL_NUMBER) {
		currentHp = 0.0f;
		// 남은 목숨이있는 경우 50% 체력 회복
		if (life > 0) {
			life--;
			currentHp = current_Status->Hp / 2;
			// HP UI 업데이트
			OnHpApply.Broadcast();
			// 수호천사 오라 해제
			OnResetAura.Broadcast();
			return;
		}
		// 캐릭터 사망
		OnHpIsZero.Broadcast();
	}


	
}

void UCharacter_Stat_Component::SetRecovery(float addHp)
{
	float newHp = FMath::Clamp<float>(currentHp + addHp, 0.0f, current_Status->Hp);
	SetHp(newHp);
}

void UCharacter_Stat_Component::SetRecovery_Percent(float addHp)
{
	float newHp = FMath::Clamp<float>(currentHp + current_Status->Hp * addHp, 0.0f, current_Status->Hp);
	SetHp(newHp);
}


float UCharacter_Stat_Component::GetHpRatio()
{
	if (currentHp <= KINDA_SMALL_NUMBER)
		currentHp = 0.0f;
	return currentHp / current_Status->Hp;
}

float UCharacter_Stat_Component::GetHp()
{
	return currentHp;
}

void UCharacter_Stat_Component::SetMode(int32 mode)
{
	Mode = mode;
}

FCharacterStat* UCharacter_Stat_Component::GetStatus()
{
	return current_Status;
}

void UCharacter_Stat_Component::SetShield(int32 NewShield)
{
	Shield = NewShield;
}

void UCharacter_Stat_Component::SetLife(int32 NewLife)
{
	life = NewLife;
}

FCharacterStat* UCharacter_Stat_Component::Getcurrent_Status()
{
	return current_Status;
}

void UCharacter_Stat_Component::SetEnemyData()
{
	// 게임인스턴스 정보 가져오기
	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance Success"));

		// 능력치 업그레이드 중 적 레벨 강화 가져오기
		TArray<int32> _statusArray = _GameInstance->statusArray;
		int32 level = _statusArray[4];

		// 근거리 적
		if (Mode == 1) {
			Default_Status = _GameInstance->Get_FEnemyMelee_Status(level);
		}
		// 원거리 적
		else if (Mode == 2) {
			Default_Status = _GameInstance->Get_FEnemyRange_Status(level);
		}		

		current_Status = new FCharacterStat();
		// Default_Status의 정보를 current_Status에 깊은 복사 해준다. 
		Default_Status->DeepCopy(current_Status);
		


		if (current_Status) {
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, School : %s"), *School);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, Hp : %f"), current_Status->Hp);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, Damage : %f"), current_Status->Damage);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, Critical : %d"), current_Status->Critical);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, CoolTime : %d"), current_Status->CoolTime);
			UE_LOG(LogTemp, Warning, TEXT("Enemy Success, percentage : %d"), current_Status->percentage);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("GameInstance ERROR"));
	}
}




