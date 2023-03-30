// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Basic_Character.h"
#include "EnemyRange_Character.h"
#include "TPS_Character.h"
#include "SPWArrow_Actor.generated.h"

UCLASS()
class TEST1_API ASPWArrow_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPWArrow_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = weapon)
		USkeletalMeshComponent* ArrowMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = weapon)
		class UBoxComponent* ArrowCollision;

	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;


	void ApplyAttack();
	void ApplyCollision();
	void DeleteCollision();

	void DestroyObj();

	void Attaching(FName AttachName);
	void Shootting();

	void SetOwner(class ABasic_Character* own);
	void SetTargetLocation(FVector targetLoc);

	void SetTargetPawn(class ATPS_Character* target);

	void SetDamage(float _damage);

	bool bIsShutt = false;

private:

	UPROPERTY(VisibleDefaultsOnly, Category = weapon)
		class ABasic_Character* MyOwner;

	FVector TargetLocation;

	FRotator rot;

	FVector dir;
	
	class ATPS_Character* Targets;

	float Damage;
};
