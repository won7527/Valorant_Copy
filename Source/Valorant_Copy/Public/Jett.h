// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Jett.generated.h"




UCLASS()
class VALORANT_COPY_API AJett : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJett();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* AKReloadingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class USkeletalMeshComponent* Mesh1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class USkeletalMeshComponent* FP_Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	float TimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	float TimeReload = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UParticleSystem* MuzzleParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay);
	class UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun);
	class USkeletalMeshComponent* FP_Shotgun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun);
	class USoundBase* ShotgunSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun)
	class USoundBase* ShotgunReloadingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun);
	class UParticleSystem* ShotgunMuzzleParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun);
	class UParticleSystem* ShotgunImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun);
	float ShotgunTimeReload = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sniper);
	class USkeletalMeshComponent* FP_Snipergun;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sniper);
	class USoundBase* SniperSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sniper);
	class USoundBase* SniperReloadingSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sniper);
	class UParticleSystem* SniperMuzzleParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sniper);
	class UParticleSystem* SniperImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sniper);
	float SniperTimeReload = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sniper);
	float SniperDelayTime = 1.5f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle_HandleRefire;
	FTimerHandle TimerHandle_Reload;
	FTimerHandle TimerHandle_ShotgunReload;
	FTimerHandle TimerHandle_SniperReload;

	FTimerHandle TimerHandle_ShotgunDelay;
	FTimerHandle TimerHandle_SniperDelay;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartFire();
	void StopFire();
	void FireShot();
	void ReloadInput();
	void Reload();
	void Weapon1Use();
	void Weapon2Use();
	void Weapon3Use();
	
	void SniperAim();
	void SniperDelay();

	void ShotgunReload();
	void SniperReload();

	void ShotgunDelay();


	int32 ammunition = 25;
	
	int32 shotgunAmmo = 8;
	int32 maxShotgunAmmo = 8;
	int32 sniperAmmo = 5;
	//playerHP
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = PlayerSetting)
	int32 playerHP = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UStaticMeshComponent* meshComp;

	void Turn(float value);

	void LookUp(float value);

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 300.0f;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float dashDistance = 3000.0f;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float jumpdashDistance = 2000.0f;

	float xValue;
	float yValue;

	bool keepPressed;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SmokeGrenade;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Knife;

	class AKnife* knife0;
	class AKnife* knife1;
	class AKnife* knife2;
	class AKnife* knife3;
	class AKnife* knife4;
	class ASmokeGrenade* smoke;
	FTimerHandle KnifeTime;
	FTimerHandle KnifeTime1;
	FTimerHandle KnifeTime2;
	FTimerHandle KnifeTime3;


	TArray< AKnife*> knifeArray;

	

	int32 MaxKnife = 0;
	FVector DeactivatedLocation;
	FVector ActivatedLocation = GetActorLocation();
		

	FVector DashDir;

	FVector direction;
	

	UFUNCTION()
	void Horizontal(float value);
	UFUNCTION()
	void Vertical(float value);
	
	void InputJump ();

	void Walking();

	void WalkEnd();

	void JumpDash();

	void Dash();

	void Smoke();

	void SmokeControlEnd();

	void KnifeSetting();

	void Fire();

	void FireSp();

	int32 GetAmmo();

	UPROPERTY(EditAnywhere, Category = Shotgun)
	int32 pellet=10;

	UPROPERTY(EditAnywhere, Category = Shotgun)
	bool isWeapon1Use = false;
	UPROPERTY(EditAnywhere, Category = Shotgun)
	bool isWeapon2Use = false;
	UPROPERTY(EditAnywhere, Category = Shotgun)
	bool isWeapon3Use = false;

	bool isBefore;
	bool after;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	bool isPlayerMoving; 

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float movingCoef;
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float movingOver6Coef;
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float sniperScopeCoef=0;


private:
	FVector ShotDirection;

	FVector rebound=FVector(0,0,0);

	FVector reboundOrigin = FVector(0, 0, 0);

	int32 recoilCount=0;

	int32 reboundCount = 0;

	//void Vertical(float AxisValue);
	//void Horizontal(float AxisValue);


	float currentTime;

	bool isFire = false;
	bool isShotgunDelay = false;
	bool isSniperDelay = false;

	float reZ;
	float reX;
	float reY;


	FVector YDir = FVector(0,0,0);
	FVector ZDir = FVector(0,0,0);

	class UMainWidget* player_UI;

	class AValorant* myGM;

	FVector BeforeVec;
	FVector AfterVec;
	
};
