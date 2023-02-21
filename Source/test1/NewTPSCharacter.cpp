// Fill out your copyright notice in the Description page of Project Settings.


#include "NewTPSCharacter.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include "Engine.h"

// Sets default values
ANewTPSCharacter::ANewTPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	
	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);


	SpringArm->TargetArmLength = 450.0f;
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}
	

// Called when the game starts or when spawned
void ANewTPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("loc : %f, %f, %f"), Camera->GetRelativeLocation().X, Camera->GetRelativeLocation().Y, Camera->GetRelativeLocation().Z));
}

void ANewTPSCharacter::ControllMode(int32 mode)
{
}

// Called every frame
void ANewTPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANewTPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 축 매핑
	InputComponent->BindAxis("MoveForward", this, &ANewTPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ANewTPSCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &ANewTPSCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ANewTPSCharacter::AddControllerPitchInput);
	// 액션 매핑
	InputComponent->BindAction("Jump", IE_Pressed, this, &ANewTPSCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ANewTPSCharacter::StopJump);
	InputComponent->BindAction("Dash", IE_Pressed, this, &ANewTPSCharacter::PressDash);
}

void ANewTPSCharacter::MoveForward(float Axisval)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Axisval);
}

void ANewTPSCharacter::MoveRight(float Axisval)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Axisval);
}

void ANewTPSCharacter::AddControllerPitchInput(float Axisval)
{
	Super::AddControllerPitchInput(Axisval);
}

void ANewTPSCharacter::StartJump()
{
	bPressedJump = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("loc : %f, %f, %f"), Camera->GetRelativeLocation().X, Camera->GetRelativeLocation().Y, Camera->GetRelativeLocation().Z));

}

void ANewTPSCharacter::StopJump()
{
	bPressedJump = false;
}

void ANewTPSCharacter::PressDash()
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

