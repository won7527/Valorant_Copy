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

	//삿건 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun);
	class USkeletalMeshComponent* FP_Shotgun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun);
	class USoundBase* ShotgunSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun);
	class UParticleSystem* ShotgunMuzzleParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shotgun);
	class UParticleSystem* ShotgunImpactParticles;
	//----------------------

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle_HandleRefire;
	FTimerHandle TimerHandle_Reload;

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

	//탄약
	int32 ammunition = 25;

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

	//총알갯수를 가져온다
	int32 GetAmmo();

	//샷건 총알 갯수
	UPROPERTY(EditAnywhere, Category = Shotgun)
	int32 pellet=10;
	


private:
	FVector ShotDirection;
	//반동값
	FVector rebound=FVector(0,0,0);
	//반동 수직 상승 값 저장
	FVector reboundOrigin = FVector(0, 0, 0);
	//카메라 피치 값
	//FRotator CamPitch;

	//카메라 반동 횟수
	int32 recoilCount=0;
	//총 반동 횟수
	int32 reboundCount = 0;

	//void Vertical(float AxisValue);
	//void Horizontal(float AxisValue);

	//현재시간
	float currentTime;

	//발사여부
	bool isFire = false;

	float reZ;
	float reX;
	float reY;

	//카메라 방향 백터 변수
	FVector YDir;
	FVector ZDir;

	//플레이어 위젯 포인터
	class UMainWidget* player_UI;
};
