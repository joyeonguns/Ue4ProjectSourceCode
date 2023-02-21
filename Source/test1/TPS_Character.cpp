// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_Character.h"
#include <Engine/Classes/Components/CapsuleComponent.h>

// Sets default values
ATPS_Character::ATPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	
	
	ControllMode(1);
	isCanJump = true;
	isCanMove = true;
	isCanRotate = true;
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("EQUIP WEAPON !!"));
	}
}

void ATPS_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATPS_Character::SpawnDefaultInventory()
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();
	FActorSpawnParameters SpawnInfo;
	UWorld* world = GetWorld();
	AWeapon_Actor* NewWeapon = world->SpawnActor<AWeapon_Actor>(DefaultInventoryClasses[0], SpawnInfo);
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
	AWeapon_Actor* LocalLastWeapon = NULL;
	if (LastWeapon != NULL) {
		LocalLastWeapon = LastWeapon;
	}

	if (NewWeapon) {
		CurrentWeapon = NewWeapon;
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}

// ============= weapon ==============


// Called when the game starts or when spawned
void ATPS_Character::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Set TPS_Character"));
	}

	SpawnDefaultInventory();

	UHUD_UserWidget* hud = CreateWidget<UHUD_UserWidget>(GetWorld(), Hud_widgetClass);
	if (hud) {
		hud->SetEnemyCount(2, 2);
		hud->SetHP(80.0f , 80.0f);
		hud->SetUlti(60.0f, 100.0f);
		hud->AddToViewport();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Hud not find"));
	}

}

void ATPS_Character::ControllMode(int32 mode)
{
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

// Called every frame
void ATPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		Axisval *= 0.5f;
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Jump!!"));		
		if (jumpCount == 1) {
			Jump();			
		}	
		else if (jumpCount == 2) {
			LaunchCharacter(FVector(0, 0, 500), false, true);
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

		GetCharacterMovement()->MaxWalkSpeed = 900;
	}
	else {
		isDash = false;
		GetCharacterMovement()->MaxWalkSpeed = 600;
	}
}

void ATPS_Character::Attack_0()
{
	//if (isDuringAttack == false) {
	//	FString PlaySection = "Attack_" + FString::FromInt(ComboAttackNum);
	//	PlayAnimMontage(DefaultAttack_Montage, 1.2f, FName(*PlaySection));
	//	ComboAttackNum++;
	//	if (ComboAttackNum > 3)
	//		ComboAttackNum = 1;
	//	
	//	
	//	
	//	isDuringAttack = true;
	//	isCanJump = false;
	//	isCanMove = false;
	//	isCanRotate = false;

	//	CurrentWeapon->ApplyAttack();

	//	// 1초후 상태 변경
	//	FTimerHandle TH_Attack0_End;
	//	GetWorldTimerManager().SetTimer(TH_Attack0_End, this, &ATPS_Character::Attack_0_End, 1.f, false);
	//}

	if (!isDuringAttack) {
		CurrentWeapon->ApplyAttack();
	}

	DefaultAttack();
	
}

//void ATPS_Character::Attack_0_End()
//{
//	isDuringAttack = false;
//	isCanJump = true;
//	isCanMove = true;
//	isCanRotate = true;
//}


