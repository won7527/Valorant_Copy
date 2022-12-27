// Fill out your copyright notice in the Description page of Project Settings.


#include "YReyna.h"
#include <GameFramework/SpringArmComponent.h> //SpringArm Component ���
#include <Camera/CameraComponent.h> //UCamera Component ���

// Sets default values
AYReyna::AYReyna()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1. ���̷�Ż�޽� �����͸� �ҷ��´�
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));

	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);

		//2.Mesh ������Ʈ�� ��ġ�� ȸ������ ����
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

		//3. ī�޶� ���ϰ��̴�
		//3-1. SpringArm������Ʈ ���̱�
		springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
		springArmComp->SetupAttachment(RootComponent);
		springArmComp->SetRelativeLocation(FVector(0, 70, 90));
		springArmComp->TargetArmLength = 400;
		//ī�޶� ȸ���� ������ ����(���콺 ������ ȭ���� ȸ���ϴ� ��)
		springArmComp->bUsePawnControlRotation = true;

		//3-2. Camera Component ���̱�
		yReynaCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("yReynaCamComp"));
		yReynaCamComp->SetupAttachment(springArmComp);

		//ī�޶� ȸ���� ������ ����(���콺 ������ ȭ���� ȸ���ϴ� ��)
		yReynaCamComp->bUsePawnControlRotation = false;
		bUseControllerRotationYaw = true;

		//4. �� skeletalMesh ������Ʈ ���
		gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));

		//4-1. �θ� ������Ʈ�� Mesh������Ʈ�� ����
		gunMeshComp->SetupAttachment(GetMesh());

		//4-2. ���̷�Ż�޽� ������ �ε�
		ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh(TEXT(""));

		//4-3. ������ �ε尡 �����ߴٸ�
		if (TempGunMesh.Succeeded())
		{
			//4-4. ���̷�Ż�޽� ������ �Ҵ�
			gunMeshComp->SetSkeletalMesh(TempGunMesh.Object);

			//4-5. ��ġ �����ϱ�
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

	//�÷��̾� �̵�ó��
	direction.Normalize();
	FVector dir = GetActorLocation() + direction * walkSpeed * DeltaTime;
	SetActorLocation(dir);

}

// Called to bind functionality to input
void AYReyna::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//�þ� ȸ��ó�� �ϴ� �Լ��� Ű���� ����(Ű����)�� �����ִ� ��
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &AYReyna::TurnRight);
	PlayerInputComponent->BindAxis(TEXT("Lookup"), this, &AYReyna::Lookup);

	//(ADWS)Ű���� �Է��Լ� ���ε�
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AYReyna::InputHorizontal);	
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AYReyna::InputVertical);

	//���� �Է� ���ε�
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AYReyna::InputJump);

	//Reload ���ε�
	PlayerInputComponent->BindAction(TEXT("BulletLoad"), IE_Pressed, this, &AYReyna::InPutBulletLoad);

	//Crouch ���ε�
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AYReyna::InputCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AYReyna::InputCrouch);

	//Fire ���ε�
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AYReyna::InputFire);

}

//�þ� ȸ��ó��
void AYReyna::TurnRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AYReyna::Lookup(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

//ĳ���� �翷 ������
void AYReyna::InputHorizontal(float value)
{
	direction.Y = value;

}

//ĳ���� ���� ������
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
	// 	//Pressed �Է�ó��
	// 	if (bTelescopeAim = false) {
	// 
	// 		//1. ���ذ� Ȱ��ȭ
	// 		bTelescopeAim = true;
	// 
	// 		//2.���ذ� UI ���
	// 		_scopeUI->AddToViewport();
	// 
	// 		//3. ī�޶� �þ߰� Field of View ����
	// 		yReynaCamComp->SetFieldOfView(45.0f);
	// 	}
	// 	
	// 	//Released �Է�ó��
	// 	else {
	// 	    //1. ���ذ� ��Ȱ��ȭ
	// 		bTelescopeAim = false;
	// 
	// 		//2.���ذ� UI ����
	// 		_scopeUI->RemoveFromViewport();
	// 
	// 		//3. ī�޶� �þ߰� ������� ����
	// 		yReynaCamComp->SetFieldOfView(90.0f);
	// 	}

}

void AYReyna::InputWeaponStorageOpen()
{

}