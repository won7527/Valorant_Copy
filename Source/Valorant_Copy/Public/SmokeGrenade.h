// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SmokeGrenade.generated.h"

UCLASS()
class VALORANT_COPY_API ASmokeGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmokeGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	void KeepPressed();
	void ReleasedC();
	void FireInDirection(const FVector& ShootDirection);
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
	float moveSpeed = 1000.0f;
	bool keepPressed;

	FVector direction;

private:
};
