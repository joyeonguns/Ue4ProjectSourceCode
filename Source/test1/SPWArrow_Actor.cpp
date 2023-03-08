// Fill out your copyright notice in the Description page of Project Settings.


#include "SPWArrow_Actor.h"
#include <Engine/Classes/Components/BoxComponent.h>
#include <Engine/Classes/Components/SkeletalMeshComponent.h>
#include "Kismet/GameplayStatics.h"

// Sets default values
ASPWArrow_Actor::ASPWArrow_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	

	ArrowCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ArrowCollision"));
	ArrowCollision->SetBoxExtent(FVector(3.f, 3.f, 3.f));	

	ArrowMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArrowMesh"));
	ArrowMesh->SetupAttachment(ArrowCollision);

	RootComponent = ArrowCollision;
}

// Called when the game starts or when spawned
void ASPWArrow_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle th;
	GetWorldTimerManager().SetTimer(th,this, &ASPWArrow_Actor::DestroyObj, 10.0f, true);
}

// Called every frame
void ASPWArrow_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShutt) {
		//SetActorRotation(rot);
		//FVector dir = MyOwner->GetActorForwardVector() * 20;
		SetActorLocation(GetActorLocation() + dir*20);

	}
}

void ASPWArrow_Actor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AActor::StaticClass())) {
		auto target = Cast<ABasic_Character>(OtherActor);
		if (target) {
			if (MyOwner != target) {
				UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Damage : 10"));

				//bIsShutt = false;
				//ArrowCollision->SetSimulatePhysics(false);
				//RootComponent->AttachToComponent(target->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			}
		}

	}

	
}

void ASPWArrow_Actor::ApplyAttack()
{
}

void ASPWArrow_Actor::ApplyCollision()
{
}

void ASPWArrow_Actor::DeleteCollision()
{
}

void ASPWArrow_Actor::DestroyObj()
{
	Destroy();
}

void ASPWArrow_Actor::Attaching(FName AttachName)
{
	if (MyOwner) {
		auto OwnerRange = Cast<AEnemyRange_Character>(MyOwner);
		if (OwnerRange) {
			USkeletalMeshComponent* PawnMessh = OwnerRange->GetSpecificPawnMesh();

			//FName AttackPoint = MyOwner->GetWeaponAttachPoint();
			//ArrowMesh->AttachTo();
			RootComponent->AttachToComponent(PawnMessh, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachName);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attaching"));
		}
		
	}
}

void ASPWArrow_Actor::Shutting()
{
	rot = GetActorRotation();
	ArrowCollision->SetSimulatePhysics(true);
	ArrowCollision->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	float Aimadd = FVector::Distance(TargetLocation, GetActorLocation()) / 6.f;

	dir = (TargetLocation + FVector(0,0, Aimadd) - GetActorLocation()).GetSafeNormal();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("loc : %f, %f, %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z) );
}

void ASPWArrow_Actor::SetOwner(ABasic_Character* own)
{
	MyOwner = own;
}

void ASPWArrow_Actor::SetTargetLocation(FVector targetLoc)
{
	TargetLocation = targetLoc;
}



