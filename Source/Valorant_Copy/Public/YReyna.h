// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YReyna.generated.h"

UCLASS()
class VALORANT_COPY_API AYReyna : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AYReyna();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//좌우 회전 입력 처리
	void TurnRight(float AxisValue);
	//상하 회전 입력 처리
	void Lookup(float AxisValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//SpringArm Component 추가
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class USpringArmComponent* springArmComp;

	//UCamera Component 추가
	UPROPERTY(VisibleAnywhere, Category = Camera)
		class UCameraComponent* yReynaCamComp;


	//이동속도
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
		float walkSpeed = 600.0f;

	//이동방향
	FVector direction;

	//좌우이동 입력 이벤트 처리 함수
	void InputHorizontal(float value);

	//상하 이동 입력 이벤트 처리 함수
	void InputVertical(float value);

	//점프 입력 이벤트 처리 함수
	void InputJump();

	//총 skeletalMesh
	UPROPERTY(VisibleAnywhere, Category = GunMesh)
		class USkeletalMeshComponent* gunMeshComp;

	//총알 장전
	void InPutBulletLoad();

	//Crouch
	void InputCrouch();

	//Fire
	void InputFire();

	//SilentStep
	void InputSilentStep();

	//TelescopeSight 조준경
	void InputTelescopeSight();

	//조준경 활성화 여부
	bool bTelescopeAim = false;

	//조준경UI 위젯공장
	UPROPERTY(EditAnywhere, Category = TelescopeUI)
		TSubclassOf<class UUserWidget> telescopeFactory;

	//조준경UI 위젯 인스턴스
	class UUserWidget* _scopeUI;

	//무기고 오픈
	void InputWeaponStorageOpen();


};
