// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBasic_Character.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy_AIController.h"
#include "DrawDebugHelpers.h"
#include "TPSPlayerController.h"
#include "TPSGameInstance.h"

AEnemyBasic_Character::AEnemyBasic_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	// ai controller 설정
	AIControllerClass = AEnemy_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Set_HpBar();

	bOnHpBar = false;
	lifeTime_HpBar = 0.0f;

	// 공격범위
	AttackRange = 150.f;
	AttackRadius = 50.0f;

	// 캐릭터 코드 값
	Status_Component->SetMode(1);
}

void AEnemyBasic_Character::Set_HpBar()
{
	//Hpbar UI 생성 및 부착
	Hp_UI = CreateDefaultSubobject<UWidgetComponent>(TEXT("HP_Bar"));
	Hp_UI->SetupAttachment(GetMesh());

	Hp_UI->SetRelativeLocation(FVector(0.0f, 0.0f, 170.0f));
	Hp_UI->SetWidgetSpace(EWidgetSpace::Screen);
	FString uipath = TEXT("WidgetBlueprint'/Game/UI/BP_HPBar.BP_HPBar_C'");
	static ConstructorHelpers::FClassFinder<UUserWidget> widget(*uipath);
	if (widget.Succeeded()) {
		Hp_UI->SetWidgetClass(widget.Class);
		Hp_UI->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
}

void AEnemyBasic_Character::BeginPlay()
{
	Super::BeginPlay();
	// Hp ui와 Status_Component 바인드
	auto CharacterWidget = Cast<UHP_UserWidget>(Hp_UI->GetUserWidgetObject());
	if (CharacterWidget) {
		CharacterWidget->BindCharacterStat(Status_Component);
	}
	// Hpbar 숨기기
	Delete_HpBar();
	bAttacking = false;
}

void AEnemyBasic_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Status_Component->OnTakeDamage.AddLambda([this]() -> void {
		bAttacking = false;
		AttackEnd();
		});	

	OnAttackEnd.AddLambda([this]() -> void {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnAttackEnd!!!"));
		});
}

void AEnemyBasic_Character::Attack()
{
	if (bAttacking == false) {

	}
}

void AEnemyBasic_Character::AttackEnd()
{
	OnAttackEnd.Broadcast();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AttackEnd!!!"));
}

void AEnemyBasic_Character::DieCharacter()
{
	if (bDead) return;
	Super::DieCharacter();

	// 레벨스크립트 함수 호출
	OnDeadDelegate.Broadcast();

	// 캐릭터가 죽을 경우 플레이어가 포인트 획득
	if (ActorHasTag("Enemy")) {
		auto gameInstace = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (gameInstace) {
			gameInstace->Point += prize;

			// 포인트 UI 적용
			auto plcont = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if (plcont) {
				plcont->GetHUD()->SetPoint(gameInstace->Point);
				plcont->GetHUD()->SetGetPoint(prize);
			}

			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta,FString::Printf(TEXT("point + %d : "), prize) );
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("DieCharacter"));
}

void AEnemyBasic_Character::AttackCheck()
{
	
}

float AEnemyBasic_Character::GetAttackRange()
{
	return AttackRange + AttackRadius;
}

void AEnemyBasic_Character::CharacterDead()
{

}

void AEnemyBasic_Character::SetPrize(int32 newPrize)
{
	prize = newPrize;
}

int32 AEnemyBasic_Character::GetPrize()
{
	return prize;
}


void AEnemyBasic_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bOnHpBar) {
		lifeTime_HpBar -= DeltaTime;
		if (lifeTime_HpBar <= 0.0f) {
			bOnHpBar = false;
			Delete_HpBar();
		}
	}
}


void AEnemyBasic_Character::DrawHpBar()
{
	if (bOnHpBar == false) {
		bOnHpBar = true;
		Hp_UI->SetVisibility(true, true);
	}

	lifeTime_HpBar = 10.0f;
}

void AEnemyBasic_Character::Delete_HpBar()
{
	bOnHpBar = false;
	Hp_UI->SetVisibility(false, false);
}

float AEnemyBasic_Character::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bDead) return Damage;
	float realDamage;

	// 크리티컬
	bool bcritical = false;
	auto Causer = Cast<ABasic_Character>(DamageCauser);

	if (Causer) {
		int32 critical = Causer->Status_Component->GetStatus()->Critical;
		int32 randNum = FMath::RandRange(0, 99);

		if (randNum < critical) bcritical = true;
	}	

	if (bcritical) {
		realDamage = Super::TakeDamage(Damage * 1.5f, DamageEvent, EventInstigator, DamageCauser);
	}
	else {
		realDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	}

	// Hpbar 보이기
	DrawHpBar();

	// 플로팅데미지 생성
	SpawnDamage(realDamage, bcritical);

	
	// 공격 받으면 플레이어를 감지함
	auto ai = Cast<AEnemy_AIController>(GetController());
	if (ai) {
		auto player = Cast<ATPS_Character>(DamageCauser);
		if (player) {
			ai->Setplayer(player);
		}
	}


	return realDamage;
}

void AEnemyBasic_Character::PossessedBy(AController* newController)
{
	Super::PossessedBy(newController);
	if (IsControlled()) {
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}

void AEnemyBasic_Character::SpawnDamage(float damage, bool critical)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	// 월드 좌표를 스크린 좌표로 변환
	FVector2D ScreenLocation;
	//PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenLocation);

	if (!PlayerController->ProjectWorldLocationToScreen(GetActorLocation() + FVector(0, 0, 100), ScreenLocation)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("ERROR"));

	}

	// UI 생성 및 띄우기
	UFloatingDamage_Widget* spwDmg = CreateWidget<UFloatingDamage_Widget>(GetWorld(), Damage_Ui);
	if (spwDmg) {
		spwDmg->SetDamage(damage, critical);
		spwDmg->SetPositionInViewport(ScreenLocation);
		spwDmg->AddToViewport();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("spwDmg Error")));

	}
}





