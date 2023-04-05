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
	
	// 생성 이후 10초 후 오브젝트 제거
	FTimerHandle th;
	GetWorldTimerManager().SetTimer(th,this, &ASPWArrow_Actor::DestroyObj, 10.0f, true);
}

// Called every frame
void ASPWArrow_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// bIsShutt 참이면 오브젝트 이동
	if (bIsShutt) {
		SetActorLocation(GetActorLocation() + dir*20);
	}
}

void ASPWArrow_Actor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// 캐릭터와 오버랩 + bIsShutt 참 일때 데미지 적용
	if (OtherActor->IsA(AActor::StaticClass())) {
		auto target = Cast<ABasic_Character>(OtherActor);
		if (target) {
			if (MyOwner != target && bIsShutt) {
				UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, MyOwner, UDamageType::StaticClass());
				Destroy();
			}
		}
	}	
}

void ASPWArrow_Actor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	// 오브젝트와 부딫힐 경우 벽에 박히는 연출
	bIsShutt = false;
	ArrowCollision->SetSimulatePhysics(false);
}


void ASPWArrow_Actor::DestroyObj()
{
	Destroy();
}

void ASPWArrow_Actor::Attaching(FName AttachName)
{
	// 부착
	if (MyOwner) {
		auto OwnerRange = Cast<AEnemyRange_Character>(MyOwner);
		if (OwnerRange) {
			USkeletalMeshComponent* PawnMessh = OwnerRange->GetSpecificPawnMesh();

			RootComponent->AttachToComponent(PawnMessh, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachName);

		}
		
	}
}

void ASPWArrow_Actor::Shootting()
{
	if (!MyOwner) return;
	// 물리 적용 -> 중력 영향 받음
	ArrowCollision->SetSimulatePhysics(true);
	// 부착 해제
	ArrowCollision->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	// 진행 방향 설정
	if (Targets) {
		TargetLocation = Targets->GetActorLocation();

		float Aimadd = FVector::Distance(TargetLocation, GetActorLocation()) / 6.f;

		dir = (TargetLocation + FVector(0, 0, Aimadd) - GetActorLocation()).GetSafeNormal();
	}
	else {
		if(MyOwner)
			dir = MyOwner->GetActorForwardVector();
	}

}

void ASPWArrow_Actor::SetOwner(ABasic_Character* own)
{
	MyOwner = own;
}

void ASPWArrow_Actor::SetTargetLocation(FVector targetLoc)
{
	TargetLocation = targetLoc;
}

void ASPWArrow_Actor::SetTargetPawn(class ATPS_Character* target)
{
	Targets = target;
}

void ASPWArrow_Actor::SetDamage(float _damage)
{
	Damage = _damage;
}



