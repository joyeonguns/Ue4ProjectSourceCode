// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBasic_Character.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy_AIController.h"

AEnemyBasic_Character::AEnemyBasic_Character()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemy_AIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Set_HpBar();

	bOnHpBar = false;
	lifeTime_HpBar = 0.0f;
}

void AEnemyBasic_Character::Set_HpBar()
{
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
	auto CharacterWidget = Cast<UHP_UserWidget>(Hp_UI->GetUserWidgetObject());
	if (CharacterWidget) {
		CharacterWidget->BindCharacterStat(Status_Component);
	}
	Delete_HpBar();
}

void AEnemyBasic_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Anim = Cast<UTPSAnimInstance>(GetMesh()->GetAnimInstance());

	if (Anim) {
		Anim->OnAttackCollision_Off.AddLambda([this]() -> void {
			UE_LOG(LogTemp, Warning, TEXT("OnAttackCollision_Off"));
			AttackEnd();
			});
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Anim_Enemy_Error"));
	}
}

void AEnemyBasic_Character::Attack()
{
	PlayAnimMontage(DefaultAttack_Montage);
}

void AEnemyBasic_Character::AttackEnd()
{
	OnAttackEnd.Broadcast();
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
	const float realDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	DrawHpBar();

	SpawnDamage(realDamage);
	return realDamage;
}

void AEnemyBasic_Character::PossessedBy(AController* newController)
{
	Super::PossessedBy(newController);
	if (IsControlled()) {
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}

void AEnemyBasic_Character::SpawnDamage(float damage)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	FVector2D ScreenLocation;
	PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ScreenLocation);

	if (!PlayerController->ProjectWorldLocationToScreen(GetActorLocation() + FVector(0, 0, 100), ScreenLocation)) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, TEXT("ERROR"));

	}

	UFloatingDamage_Widget* spwDmg = CreateWidget<UFloatingDamage_Widget>(GetWorld(), Damage_Ui);
	if (spwDmg) {
		spwDmg->SetDamage(damage);
		spwDmg->SetPositionInViewport(ScreenLocation);
		spwDmg->AddToViewport();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("spwDmg Error")));

	}
}





