// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ValEnemy.generated.h"

UCLASS()
class VALORANT_COPY_API AValEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AValEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComponent)
	class UFSM* fsm;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	class UStaticMeshComponent* HPRed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	class UStaticMeshComponent* HPBlack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UParticleSystem* MuzzleParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UParticleSystem* DeathParticles;

	class AJett* Jett;

	int32 ammunition = 25;
	
	float MaxHp;
	
	float HP;

	float HPRate;
	
	FTimerHandle cooltime;

	bool isDelay = false;

	void Fire();

	void FireDelay();

	void FireDelayEnd();

	void Attacked(int32 deal);

	void EnemyAllDestory();

	float cur;
	bool ismove=false;
	bool isturn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyMoveSetting);
	bool enemyMoveSet = true;

	bool isPlayerDetected = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyMoveSetting);
	FHitResult Hit_detect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemyMoveSetting);
	float sightDetectRange = 0.5f;




	

};
