// Fill out your copyright notice in the Description page of Project Settings.


#include "YReyna.h"
#include <GameFramework/SpringArmComponent.h> //SpringArm Component 등록
#include <Camera/CameraComponent.h> //UCamera Component 등록

// Sets default values
AYReyna::AYReyna()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1. 스켈레탈메시 데이터를 불러온다
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));

	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);

		//2.Mesh 컴포넌트의 위치와 회전값을 설정
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

		//3. 카메라를 붙일것이다
		//3-1. SpringArm컴포넌트 붙이기
		springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
		springArmComp->SetupAttachment(RootComponent);
		springArmComp->SetRelativeLocation(FVector(0, 70, 90));
		springArmComp->TargetArmLength = 400;
		//카메라 회전과 관련한 설정(마우스 돌릴때 화면이 회전하는 것)
		springArmComp->bUsePawnControlRotation = true;

		//3-2. Camera Component 붙이기
		yReynaCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("yReynaCamComp"));
		yReynaCamComp->SetupAttachment(springArmComp);

		//카메라 회전과 관련한 설정(마우스 돌릴때 화면이 회전하는 것)
		yReynaCamComp->bUsePawnControlRotation = false;
		bUseControllerRotationYaw = true;

		//4. 총 skeletalMesh 컴포넌트 등록
		gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));

		//4-1. 부모 컴포넌트를 Mesh컴포넌트로 설정
		gunMeshComp->SetupAttachment(GetMesh());

		//4-2. 스켈레탈메시 데이터 로드
		ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh(TEXT(""));

		//4-3. 데이터 로드가 성공했다면
		if (TempGunMesh.Succeeded())
		{
			//4-4. 스켈레탈메시 데이터 할당
			gunMeshComp->SetSkeletalMesh(TempGunMesh.Object);

			//4-5. 위치 조정하기
			gunMeshComp->SetRelativeLocationAndRotation((FVector(-60, 3.6f, 96)), FRotator(0, 0, 90.f));
		}
	}

}

// Called when the game starts or when spawned
void AYReyna::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYReyna::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//플레이어 이동처리
	direction.Normalize();
	FVector dir = GetActorLocation() + direction * walkSpeed * DeltaTime;
	SetActorLocation(dir);

}

// Called to bind functionality to input
void AYReyna::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//시야 회전처리 하는 함수를 키보드 설정(키맵핑)과 묶어주는 것
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &AYReyna::TurnRight);
	PlayerInputComponent->BindAxis(TEXT("Lookup"), this, &AYReyna::Lookup);

	//(ADWS)키보드 입력함수 바인딩
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AYReyna::InputHorizontal);	
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AYReyna::InputVertical);

	//점프 입력 바인딩
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AYReyna::InputJump);

	//Reload 바인딩
	PlayerInputComponent->BindAction(TEXT("BulletLoad"), IE_Pressed, this, &AYReyna::InPutBulletLoad);

	//Crouch 바인딩
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AYReyna::InputCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AYReyna::InputCrouch);

	//Fire 바인딩
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AYReyna::InputFire);

}

//시야 회전처리
void AYReyna::TurnRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AYReyna::Lookup(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

//캐릭터 양옆 움직임
void AYReyna::InputHorizontal(float value)
{
	direction.Y = value;

}

//캐릭터 상하 움직임
void AYReyna::InputVertical(float value)
{
	direction.X = value;
}

void AYReyna::InputJump()
{
	Jump();
}

void AYReyna::InPutBulletLoad()
{

}

void AYReyna::InputCrouch()
{

}

void AYReyna::InputFire()
{

}

void AYReyna::InputSilentStep()
{

}

void AYReyna::InputTelescopeSight() {

	// 	if (bTelescopeAim) {
	// 		return;
	// 	}
	// 
	// 	//Pressed 입력처리
	// 	if (bTelescopeAim = false) {
	// 
	// 		//1. 조준경 활성화
	// 		bTelescopeAim = true;
	// 
	// 		//2.조준경 UI 등록
	// 		_scopeUI->AddToViewport();
	// 
	// 		//3. 카메라 시야각 Field of View 설정
	// 		yReynaCamComp->SetFieldOfView(45.0f);
	// 	}
	// 	
	// 	//Released 입력처리
	// 	else {
	// 	    //1. 조준경 비활성화
	// 		bTelescopeAim = false;
	// 
	// 		//2.조준경 UI 해제
	// 		_scopeUI->RemoveFromViewport();
	// 
	// 		//3. 카메라 시야각 원래대로 복원
	// 		yReynaCamComp->SetFieldOfView(90.0f);
	// 	}

}

void AYReyna::InputWeaponStorageOpen()
{

}