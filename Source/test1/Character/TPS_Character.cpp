// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_Character.h"
#include "TPSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include "TPSGameInstance.h"


// Sets default values
ATPS_Character::ATPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	Status_Component->SetMode(0);
	
	ControllMode(1);
	isCanJump = true;
	isCanMove = true;
	isCanRotate = true;


	// 스킬 쿨타임 설정
	Def_CooTime_Q = 10.0f;
	Def_CooTime_E = 10.0f;
	Def_CooTime_1 = 10.0f;
	Def_CooTime_2 = 10.0f;

	// playerController 할당
	playerController = Cast<ATPSPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}


// ============= weapon ==============
USkeletalMeshComponent* ATPS_Character::GetSpecificPawnMesh() const
{
	return GetMesh();
}

FName ATPS_Character::GetWeaponAttachPoint() const
{
	return WeaponAttackPoint;
}

void ATPS_Character::EquipWeapon(AWeapon_Actor* Weapon)
{
	if (Weapon) {
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ATPS_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Status_Component 델리케이트 함수 연결
	Status_Component->OnHpIsZero.AddLambda([this]() -> void {
		if (playerController) {
			playerController->InputKeyESC();
		}
		});
	Status_Component->OnTakeDamage_Param.AddUObject(this, &ATPS_Character::TakeDamageAplly);


	// AnimInstance 델리게이트 함수 연결
	Anim = Cast<UTPSAnimInstance>(GetMesh()->GetAnimInstance());

	if (Anim) {

		Anim->OnApplySkill_Q_Delegate.AddLambda([this]() -> void {
			FTimerHandle TH;
			GetWorldTimerManager().SetTimer(TH, this, &ATPS_Character::SpwnObjSkill_Q, 0.1f, false);
			FTimerHandle TH_1;
			GetWorldTimerManager().SetTimer(TH_1, this, &ATPS_Character::SpwnObjSkill_Q_1, 0.4f, false);
			FTimerHandle TH_2;
			GetWorldTimerManager().SetTimer(TH_2, this, &ATPS_Character::SpwnObjSkill_Q_2, 0.7f, false);
			});

		Anim->OnUseItem_Delegate.AddLambda([this]() -> void{
			TakeShock();
			});
		Anim->OnEndHeal_Delegate.AddLambda([this]() -> void {
			EndShock();
			UseHealingItem();
			});

		Anim->OnApplyReinforce_Delegate.AddLambda([this]() -> void {
			ApplyReinforce();
			});
		Anim->OnEndMotion_Delegate.AddLambda([this]() -> void {
			EndShock();
			});

		Anim->OnDashSlash_Delegate.AddUObject(this, &ATPS_Character::DashFront);

		Anim->OnSpawnGhost_Delegate.AddUObject(this, &ATPS_Character::SpawnGhostTail);

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AnimError"));
	}
}

void ATPS_Character::SpawnDefaultInventory(int32 itemCode)
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();
	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();
	AWeapon_Actor* NewWeapon = world->SpawnActor<AWeapon_Actor>(DefaultInventoryClasses[itemCode], SpawnInfo);
	AddWeapon(NewWeapon);

	if (Inventory.Num() > 0) {
		EquipWeapon(Inventory[0]);
	}
}

void ATPS_Character::AddWeapon(AWeapon_Actor* Weapon)
{
	if (Weapon) {
		Inventory.AddUnique(Weapon);
	}
}

void ATPS_Character::SetCurrentWeapon(AWeapon_Actor* NewWeapon, AWeapon_Actor* LastWeapon)
{
	if (CurrentWeapon) {
		CurrentWeapon->Destroy();
	}

	AWeapon_Actor* LocalLastWeapon = NULL;
	if (LastWeapon != NULL) {
		LocalLastWeapon = LastWeapon;
	}

	if (NewWeapon) {
		NewWeapon->SetActorLocation(FVector::ZeroVector);
		CurrentWeapon = NewWeapon;
		NewWeapon->SetOwningPawn(this);
		EquipWeapon();
	}
}

void ATPS_Character::EquipWeapon()
{
	if (CurrentWeapon) {
		CurrentWeapon->AttachMeshToPawn(WeaponAttackPoint);
	}
}

void ATPS_Character::DisArmWeapon()
{
	if (CurrentWeapon) {
		CurrentWeapon->AttachMeshToPawn(DisarmPoint);
	}
}

void ATPS_Character::TakeShock()
{
	Super::TakeShock();
	CurrentWeapon->DeleteCollision();
}

float ATPS_Character::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float realDamage;

	// 크리티컬 
	bool bcritical = false;
	auto Causer = Cast<ABasic_Character>(DamageCauser);

	int32 critical = Causer->Status_Component->GetStatus()->Critical;
	int32 randNum = FMath::RandRange(0, 99);

	if (randNum < critical) bcritical = true;

	if (bcritical) {
		// 크리티컬
		realDamage = Super::TakeDamage(Damage * 1.5f, DamageEvent, EventInstigator, DamageCauser);
	}
	else {
		// 크리티컬 X
		realDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	}

	

	return realDamage;
}

// ============= weapon ==============


// Called when the game starts or when spawned
void ATPS_Character::BeginPlay()
{
	Super::BeginPlay();
	
	// OnHpApply 호출시 Hpbar상태 업데이트
	Status_Component->OnHpApply.AddUObject(this, &ATPS_Character::HpUIAplly);
	
	// 초기 상태 값 
	bDisarm = false;
	current_CooTime_Q = 10.0f;
	current_CooTime_E = 10.0f;
	current_CooTime_1 = 10.0f;
	current_CooTime_2 = 10.0f;
	
	// SchoolCode 초기화
	FString School = Status_Component->Getcurrent_Status()->School;
	SchoolCode = 0;
	if (School == "fire") {
		SchoolCode = 1;
	}
	else if (School == "volt") {
		SchoolCode = 2;
	}
	else if (School == "aqua") {
		SchoolCode = 3;
	}

	// 아이템 가득 
	SetItemCount_Heal(MaxItemCount_Heal);
	SetItemCount_Reinforce(MaxCount_Reinforce);

	// 포인트UI 설정
	auto gameInstace = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstace) {
		if (playerController) {
			playerController->GetHUD()->SetPoint(gameInstace->Point);
		}
	}

}

void ATPS_Character::ControllMode(int32 mode)
{
	// 카메라 및 스프링 암 조정
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->TargetArmLength = 450.0f;
	SpringArmComponent->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bInheritPitch = true;
	SpringArmComponent->bInheritRoll = true;
	SpringArmComponent->bInheritYaw = true;
	SpringArmComponent->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);	
}

void ATPS_Character::SpwnObjSkill_Q()
{
	FVector dir = GetActorForwardVector() * FVector(1,1,0);
	FVector spwLoc = GetActorLocation();
	FRotator spwRot = GetActorRotation();

	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();

	if (world) {
		AActor_SpawnSkill_Q* skillEffect_0 = world->SpawnActor<AActor_SpawnSkill_Q>(Spw_SkillEffectClass_Q_Array[SchoolCode], spwLoc + dir * 200, spwRot, SpawnInfo);
		skillEffect_0->SetOwner(this);
		skillEffect_0->SetDamage(Status_Component->Getcurrent_Status()->Damage + 20);

		skillEffect_0->School = Status_Component->Getcurrent_Status()->School;
	}
	
}
void ATPS_Character::SpwnObjSkill_Q_1()
{
	FVector dir = GetActorForwardVector() * FVector(1, 1, 0);
	FVector spwLoc = GetActorLocation();
	FRotator spwRot = GetActorRotation();

	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();

	if (world) {
		AActor_SpawnSkill_Q* skillEffect_1 = world->SpawnActor<AActor_SpawnSkill_Q>(Spw_SkillEffectClass_Q_Array[SchoolCode], spwLoc + dir * 800, spwRot, SpawnInfo);
		skillEffect_1->SetOwner(this);
		skillEffect_1->SetDamage(Status_Component->Getcurrent_Status()->Damage + 20);
		skillEffect_1->School = Status_Component->Getcurrent_Status()->School;
	}
}
void ATPS_Character::SpwnObjSkill_Q_2()
{
	FVector dir = GetActorForwardVector() * FVector(1, 1, 0);
	FVector spwLoc = GetActorLocation();
	FRotator spwRot = GetActorRotation();

	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();

	if (world) {
		AActor_SpawnSkill_Q* skillEffect_2 = world->SpawnActor<AActor_SpawnSkill_Q>(Spw_SkillEffectClass_Q_Array[SchoolCode], spwLoc + dir * 1400, spwRot, SpawnInfo);
		skillEffect_2->SetOwner(this);
		skillEffect_2->SetDamage(Status_Component->Getcurrent_Status()->Damage + 20);
		skillEffect_2->School = Status_Component->Getcurrent_Status()->School;
	}

}

void ATPS_Character::DashFront()
{
	// 전진 배기

	// 전진 방향 설정
	FRotator rot = GetActorRotation();
	FRotator YawRotation(0, rot.Yaw, 0);

	FVector dir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	
	// 마찰력 0.0f 설정 
	GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
	// 캐릭터 전진
	LaunchCharacter(dir * 10000, true, true);

	// 0.1초후 캐릭터 멈춤
	FTimerHandle th;
	GetWorldTimerManager().SetTimer(th, this, &ATPS_Character::StopDash, 0.1f, false);
	
	// 시간을 5배 느리게함
	GetWorldSettings()->SetTimeDilation(0.2f);

	// 캐릭터가 벽과 다른 캐릭터를 통과하기 위해 매쉬와 캡슐컴포넌트 NoCollision
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	// 멀티채널로 Hit 감지
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Param(NAME_None, false, this);
	bool bResult = GetWorld()->SweepMultiByChannel(
		HitResults,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 1000.f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(150.0f),
		Param
	);

	// 디버그 프린팅
#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * 1000;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = 1000 * 0.5f + 50;
	FQuat CapsulRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLife = 1.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		150,
		CapsulRot,
		DrawColor,
		false,
		DebugLife
	);


#endif // ENABLE_DRAW_DEBUG

	// 부딫힌 적들에게 데미지 적용
	if (bResult) {
		for (auto hit : HitResults) {
			if (hit.Actor.IsValid()) {
				if (hit.Actor->ActorHasTag("Enemy")) {
					FDamageEvent DamageEvent;
					float Damage = Status_Component->Getcurrent_Status()->Damage * 2;

					hit.Actor->TakeDamage(Damage, DamageEvent, GetController(), this);
				}
			}
		}		
	}
}

void ATPS_Character::StopDash()
{
	// 캐릭터의 속도를 멈춘다.
	GetCharacterMovement()->StopMovementImmediately();

	// 마찰력 초기화
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
	
	// 월드 시간딜레이 초기화
	GetWorldSettings()->SetTimeDilation(1.0f);

	// 컬리전 초기롸
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

}

void ATPS_Character::Rolling()
{
	// 구르기 수행
	if (!broll) {
		TakeShock();

		broll = true;
		currentRollingTime = 0.0f;
		rollStartLoc = GetActorLocation();

		FVector dir = GetActorForwardVector();

		rollEndLoc = rollStartLoc + dir * 700;

		// 애님몽타주 실행
		if(RollingFront_AnimMontage)
			PlayAnimMontage(RollingFront_AnimMontage , 1/0.7f);

		// 잔상 생성
		SpawnGhostTail();

	}
}

void ATPS_Character::MoveRolling(float deltaTime)
{
	// Tick 함수에서 실행
	if (broll) {
		currentRollingTime += deltaTime;

		FVector dir = (rollEndLoc - rollStartLoc).GetSafeNormal();

		// Lerp를 통해 캐릭터 위치 변경
		SetActorLocation(FMath::Lerp(rollStartLoc, rollEndLoc, currentRollingTime / RollingDuration));

		// Notifyhit 함수를 호출하기위해 캐릭터에 힘을 가함
		LaunchCharacter(dir, false, false);

		// 구르기 끝
		if (currentRollingTime >= RollingDuration) {
			CurrentReinforceTime = RollingDuration;
			broll = false;
			EndShock();
		}
	}
}

void ATPS_Character::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	// 벽에 부딫힐 경우 구르기 목표 위치 초기화
	if (Other->ActorHasTag("Wall")) {
		currentRollingTime = RollingDuration;
		rollEndLoc = GetActorLocation();

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Overlap Wall"));
	}
}

void ATPS_Character::SpawnGhostTail()
{
	// 잔상 생성

	FVector spwLoc = GetActorLocation() - FVector(0,0,90);
	FRotator spwRot = GetActorRotation() - FRotator(0,90,0);
	FActorSpawnParameters spwInfo;


	auto GhostTailInstance = GetWorld()->SpawnActor<AActor_GhostTail>(SpawnGhostClass, spwLoc, spwRot, spwInfo);
	if (GhostTailInstance) {
		GhostTailInstance->Init(GetMesh());
	}
}

void ATPS_Character::SpwnReinforceAura()
{
	if (ReinforceEffect != nullptr) return;

	FActorSpawnParameters SpwInfo;
	ReinforceEffect = GetWorld()->SpawnActor<AActor>(Array_ReinforceEffectClass[0], SpwInfo);

	if (ReinforceEffect) {
		//ReinforceEffect->GetRootComponent()->AttachTo(GetMesh(), "Reinforce");
		ReinforceEffect->SetActorLocation(FVector(0, 0, -88));
		ReinforceEffect->GetRootComponent()->AttachTo(GetCapsuleComponent());
	}
}

void ATPS_Character::EndReinforce()
{
	if (ReinforceEffect) {
		ReinforceEffect->Destroy();
	}
}

void ATPS_Character::ApplyReinforce()
{
	if (!bReinforce) {
		SpwnReinforceAura();
	}

	// Reinforce아이템 횟수 감소
	SetItemCount_Reinforce(CurrentCount_Reinforce - 1);
	
	bReinforce = true;
	coolDown_2 = false;
	current_CooTime_2 = 0.0f;
	CurrentReinforceTime = 0.0f;
}

void ATPS_Character::SetItemCount_Reinforce(int32 itemCount)
{
	CurrentCount_Reinforce = itemCount;
	if (CurrentCount_Reinforce > MaxCount_Reinforce) {
		CurrentCount_Reinforce = MaxCount_Reinforce;
	}

	if (playerController != nullptr) {
		// Reinforce 아이템 횟수 UI적용 
		playerController->GetHUD()->SetItemCount_2(CurrentCount_Reinforce);
	}
}

void ATPS_Character::InputInterection()
{
	OnInteraction.Broadcast();
}


void ATPS_Character::ApplyBuff_Heart()
{
	Super::ApplyBuff_Heart();

	//아이템 횟수 초기화
	SetItemCount_Heal(MaxItemCount_Heal);
}

void ATPS_Character::ApplyBuff_Energy()
{
	Super::ApplyBuff_Energy();

	// 특성 확률 2배 증가
	auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (_GameInstance) {
		_GameInstance->BattleData_Player->School_Percent *=2;
	}

}

void ATPS_Character::ApplyBuff_Arcane()
{
	Super::ApplyBuff_Arcane();
	if (Status_Component) {
		// 스킬가속 증가
		Skill_Acceleration = Status_Component->Getcurrent_Status()->CoolTime + AddSpeed;

		// 캐릭터 전투스텟정보 할당
		auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (_GameInstance) {
			_GameInstance->BattleData_Player->Speed = AddSpeed;
			_GameInstance->BattleData_Player->Accel_CoolTime += AddSpeed;
		}
	}	
}

void ATPS_Character::ApplyBuff_Dia()
{
	Super::ApplyBuff_Dia();
}

void ATPS_Character::ApplyBuff_Shield()
{
	Super::ApplyBuff_Shield();
}

void ATPS_Character::ResetBuff()
{	
	if (ApplyBuffCode == 3) {
		Skill_Acceleration = Status_Component->Getcurrent_Status()->CoolTime;

		// 캐릭터 전투스텟정보 할당
		auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (_GameInstance) {
			_GameInstance->BattleData_Player->Speed = 0;
			_GameInstance->BattleData_Player->Accel_CoolTime -= AddSpeed;
		}		
	}
	else if (ApplyBuffCode == 2) {
		// Energy 버프 초기화
		auto _GameInstance = Cast<UTPSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (_GameInstance) {
			_GameInstance->BattleData_Player->School_Percent /= 2;
		}
	}
	Super::ResetBuff();
}

// Called every frame
void ATPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 스킬 가속
	float AccellTime = DeltaTime * (100 + Skill_Acceleration) * 0.01f;

	// 스킬 쿨타임 계산
	if (coolDown_Q == false) {
		current_CooTime_Q += AccellTime;
		if (current_CooTime_Q >= Def_CooTime_Q) {
			coolDown_Q = true;
		}
	}

	if (coolDown_E == false) {
		current_CooTime_E += AccellTime;
		if (current_CooTime_E >= Def_CooTime_E) {
			coolDown_E = true;
		}
	}

	if (coolDown_1 == false) {
		current_CooTime_1 += AccellTime;
		if (current_CooTime_1 >= Def_CooTime_1) {
			coolDown_1 = true;
		}
	}

	if (coolDown_2 == false) {
		current_CooTime_2 += AccellTime;
		if (current_CooTime_2 >= Def_CooTime_2) {
			coolDown_2 = true;
		}
	}

	// Reinforce 버프효과
	if (bReinforce) {
		CurrentReinforceTime += DeltaTime;
		if (Status_Component != nullptr) {
			Status_Component->SetRecovery(DeltaTime * 10);
		}

		if (CurrentReinforceTime >= ReinforceDuration) {
			bReinforce = false;
			CurrentReinforceTime = ReinforceDuration;
			EndReinforce();
		}
	}

	// 스킬 쿨다운 UI 적용
	playerController->HUDCoolDownUpdate(Def_CooTime_Q ,current_CooTime_Q  ,
		Def_CooTime_E, current_CooTime_E,
		Def_CooTime_1, current_CooTime_1,
		Def_CooTime_2, current_CooTime_2);


	// 구르기 
	MoveRolling(DeltaTime);

}

// Called to bind functionality to input
void ATPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 축 매핑
	InputComponent->BindAxis("MoveForward", this, &ATPS_Character::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATPS_Character::MoveRight);
	InputComponent->BindAxis("Turn", this, &ATPS_Character::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ATPS_Character::AddControllerPitchInput);
	// 액션 매핑
	InputComponent->BindAction("Jump", IE_Pressed, this, &ATPS_Character::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ATPS_Character::StopJump);
	InputComponent->BindAction("Dash", IE_Pressed, this, &ATPS_Character::PressDash);
	InputComponent->BindAction("Attack_0", IE_Pressed, this, &ATPS_Character::Attack_0);
	InputComponent->BindAction("Disarm", IE_Pressed, this, &ATPS_Character::Disarm);
	InputComponent->BindAction("skill_Q", IE_Pressed, this, &ATPS_Character::InputSkill_Q);
	InputComponent->BindAction("skill_E", IE_Pressed, this, &ATPS_Character::InputSkill_E);
	InputComponent->BindAction("item_1", IE_Pressed, this, &ATPS_Character::InputItem_1);
	InputComponent->BindAction("item_2", IE_Pressed, this, &ATPS_Character::InputItem_2);
	InputComponent->BindAction("Interaction", IE_Pressed, this, &ATPS_Character::InputInterection);
	InputComponent->BindAction("Rolling", IE_Pressed, this, &ATPS_Character::Rolling);
	
}

void ATPS_Character::MoveForward(float Axisval)
{
	if (isCanMove) {
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Axisval);
	}
}

void ATPS_Character::MoveRight(float Axisval)
{
	if (isCanMove) {
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		
		
		AddMovementInput(Direction, Axisval);
	}
	
}

void ATPS_Character::AddControllerPitchInput(float Axisval)
{	
	if (isCanRotate) {
		//Axisval *= 0.5f;
		Super::AddControllerPitchInput(Axisval);
	}
	
}

void ATPS_Character::AddControllerYawInput(float Axisval)
{
	if (isCanRotate) {
		Super::AddControllerYawInput(Axisval);
	}
	
}

void ATPS_Character::Landed(const FHitResult& Hit)
{
	jumpCount = 0;
}

void ATPS_Character::StartJump()
{
	if (isCanJump) {	
		jumpCount++;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Jump!!"));		
		if (jumpCount == 1) {
			Jump();			
		}	
		else if (jumpCount == 2) {
			// 더블 점프
			LaunchCharacter(FVector(0, 0, 500), false, true);

			if(DoubleJump_AnimMontage)
				PlayAnimMontage(DoubleJump_AnimMontage);
		}		
	}
}

void ATPS_Character::StopJump()
{
	if (isCanJump) {
		//bPressedJump = false;
	}
	
}

void ATPS_Character::PressDash()
{
	// 대쉬 온
	if (isDash == false) {
		isDash = true;
		realMoveSpeed = DefaultRunSpeed;
		SetMoveSpeed();
	}
	else {
		isDash = false;
		realMoveSpeed = DefaultWalkSpeed;
		SetMoveSpeed();
	}
}

void ATPS_Character::Attack_0()
{	
	if (bDisarm) return;

	if (!isDuringAttack && !bShocking) {
		// 무기 컬리전 변경
		CurrentWeapon->ApplyAttack();
	}

	// 공격
	DefaultAttack(Attack_Speed);	
}

void ATPS_Character::Disarm()
{
	if (bDisarm) {
		bDisarm = false;
		
		if(Armed_AnimMontage)
			PlayAnimMontage(Armed_AnimMontage);

		FTimerHandle TH_Equip;
		GetWorldTimerManager().SetTimer(TH_Equip, this, &ATPS_Character::EquipWeapon, 1.f, false);		
	}
	else {
		bDisarm = true;

		if(Disarm_AnimMontage)
			PlayAnimMontage(Disarm_AnimMontage);

		FTimerHandle TH_Disarm;
		GetWorldTimerManager().SetTimer(TH_Disarm, this, &ATPS_Character::DisArmWeapon, 1.f, false);

	}
}


void ATPS_Character::SetGroundFriction(float friction)
{
	GetCharacterMovement()->GroundFriction = friction;
}

void ATPS_Character::ResetGroundFriction()
{
	GetCharacterMovement()->GroundFriction = 8.0f;
}

void ATPS_Character::HpUIAplly()
{
	// Hpbar UI 적용
	if (playerController) {
		playerController->GetHUD()->SetHP(Status_Component->GetHpRatio(), 1.f);
	}

}

void ATPS_Character::TakeDamageAplly(float _damage)
{
	// 데미지 수치 UI 적용
	if (playerController) {
		playerController->GetHUD()->SetTakeDamage(_damage);
	}
}

void ATPS_Character::InputSkill_Q()
{
	if (bDisarm) return;

	if (bShocking == false && isDuringAttack == false && coolDown_Q) {

		coolDown_Q = false;
		current_CooTime_Q = 0.0f;

		if(Skill_Q_AnimMontage)
			PlayAnimMontage(Skill_Q_AnimMontage);		
		

		isDuringAttack = true;
		isCanJump = false;
		isCanMove = false;
		isCanRotate = false;
	}
	
}

void ATPS_Character::InputSkill_E()
{
	if (bDisarm) return;

	if (bShocking == false && isDuringAttack == false && coolDown_E) {

		coolDown_E = false;
		current_CooTime_E = 0.0f;

		if(Skill_E_AnimMontage)
			PlayAnimMontage(Skill_E_AnimMontage);


		isDuringAttack = true;
		isCanJump = false;
		isCanMove = false;
		isCanRotate = false;
	}
}

void ATPS_Character::InputItem_1()
{
	if (bShocking || isDuringAttack || jumpCount) return;
	
	if (coolDown_1 && CurrentItemCount_Heal > 0) {
		if(Healing_AnimMontage)
			PlayAnimMontage(Healing_AnimMontage);		
	}
}

void ATPS_Character::InputItem_2()
{
	if (bShocking || isDuringAttack || jumpCount) return;

	if (coolDown_2 && CurrentCount_Reinforce > 0) {
		if(Reinforce_AnimMontage)
			PlayAnimMontage(Reinforce_AnimMontage);
	}
}

void ATPS_Character::UseHealingItem()
{
	if (Status_Component == nullptr) return;

	coolDown_1 = false;
	current_CooTime_1 = 0.0f;

	Status_Component->SetRecovery_Percent(0.3f);
	SetItemCount_Heal(CurrentItemCount_Heal - 1);

}

void ATPS_Character::SetItemCount_Heal(int32 itemCount)
{
	CurrentItemCount_Heal = itemCount;
	if (CurrentItemCount_Heal > MaxItemCount_Heal) {
		CurrentItemCount_Heal = MaxItemCount_Heal;
	}

	// UI 적용
	if (playerController == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("playerController Null"));
		return;
	}

	playerController->GetHUD()->SetItemCount_1(CurrentItemCount_Heal);
}





