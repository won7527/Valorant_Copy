// Fill out your copyright notice in the Description page of Project Settings.


#include "YReyna.h"
#include <GameFramework/SpringArmComponent.h> //SpringArm Component ���
#include "GameFramework/Actor.h"
#include <Kismet/GameplayStatics.h>
#include <Camera/CameraComponent.h> //UCamera Component ���

// Sets default values
AYReyna::AYReyna()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1. ���̷�Ż�޽� �����͸� �ҷ��´�
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		TempMesh(TEXT("SkeletalMesh'/Game/Characters/Mannequin_UE4/Meshes/SK_Mannequin.SK_Mannequin'"));

	
		//1��Ī �������� ���̴� ī�޶� ������Ʈ ����
		yReynaCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		check(yReynaCamComp != nullptr);

		//ĸ��������Ʈ�� ī�޶� ������Ʈ ���̱�
		yReynaCamComp->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

		//ī�޶� ��ġ �������� ���߱�
		yReynaCamComp->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));

		//ī�޶� ȸ���� pawn�� ��Ʈ�� �� �� �ֵ���
		yReynaCamComp->bUsePawnControlRotation = true;

		//1��Ī �Ž�������Ʈ(�÷��� ����ڿ�) ����
		FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		check(FPSMesh != nullptr);

		//�÷����ϴ� ����ڸ� 1��Ī������ ���� �� �� �ֵ���
		FPSMesh->SetOnlyOwnerSee(true);

		//FpsMesh�� Fps camera �����ϱ�
		FPSMesh->SetupAttachment(yReynaCamComp);

		//1��Ī mesh�� �׸��� ���� �ʵ���
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;

		//�÷��� ����ڰ� 3��Ī ĳ���͸Žô� �Ⱥ��̵���
		GetMesh()->SetOnlyOwnerSee(true);

	if (TempMesh.Succeeded())
	{

		//4. �� skeletalMesh ������Ʈ ���
		gunMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMeshComp"));

		//4-1. �θ� ������Ʈ�� Mesh������Ʈ�� ����
		gunMeshComp->SetupAttachment(GetMesh());

		//4-2. ���̷�Ż�޽� ������ �ε�
		ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh(TEXT("SkeletalMesh'/Game/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));

		//4-3. ������ �ε尡 �����ߴٸ�
		if (TempGunMesh.Succeeded())
		{
		//4-4. ���̷�Ż�޽� ������ �Ҵ�
		gunMeshComp->SetSkeletalMesh(TempGunMesh.Object);

		//4-5. ��ġ �����ϱ�
		gunMeshComp->SetRelativeLocationAndRotation((FVector(-59.3f, 3.34f, 94.86f)), FRotator(0, 0, 90.f));
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
	Reynadirection.Normalize();
	FVector dir = GetActorLocation() + Reynadirection * walkSpeed * DeltaTime;
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
	PlayerInputComponent->BindAction(TEXT("BulletLoad"), IE_Pressed, this, &AYReyna::BulletLoad);

	//Crouch ���ε�
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AYReyna::InputCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AYReyna::InputCrouch);

	//Fire ���ε�
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AYReyna::Fire);

	//EyeShot Skill ���ѽ�ų Ű���� C ����
	PlayerInputComponent->BindAction(TEXT("EyeShotSkill"), IE_Pressed, this, &AYReyna::EyeShotSkill);

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
	Reynadirection.Y = value;

}

//ĳ���� ���� ������
void AYReyna::InputVertical(float value)
{
	Reynadirection.X = value;
}

void AYReyna::InputJump()
{
	Jump();
}

void AYReyna::BulletLoad()
{

}

void AYReyna::InputCrouch()
{

}

void AYReyna::Fire() 
{
    //������� YReynaile�� ProjectileClass�� �����Ұ��̴�.
	if (ProjectileClass) 
	{
		//ī�޶� ��ġ ���
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation); //�����̼���(?)

		//ī�޶� �տ����� �ѱ�(Muzzle) ��ġ�� �뷫������ �����Ѵ�
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		//ī�޶� �տ� ������ �ѱ��� ��ġ�� world��(world location ���� �����ε�)
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation). TransformVector(MuzzleOffset);

		//Skew the aim to be slightly upwards(�������� ��¦ �񽺵��� �����϶�?) Skew : �񽺵��� �����̴�
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		//UWorld* World = GetWorld(); 
		//�� �־����� �𸣰����� �ϴ� �ּ����� �ڰ� �Լ� ��ü�� ����Ͽ� �����Ұ��̴� 
		//GetWorld()-> �̷��� ������ָ� �ȴ�.

		if (GetWorld()) 
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator(); 
			
			//instigator�� �����ڷ� ������ ��.
			//���� ���͸� ȭ��� �����Ѵ� >> instigator�� ��(ĳ���Ͱ� �߻���Ų ������)

			AYReynaile* Projectile = GetWorld()->SpawnActor<AYReynaile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			//if (Projectile) {

				//projectile(�浹ü(?))�� ���� �����ϱ� (Set the projectile's initial trajectory)
				FVector LaunchDirection = MuzzleRotation.Vector();

				//���̳��� �������� ���� �߻��ϴ� ������ �����Ұ��̴�
				//(AYReyna::Projectile)->(AYReynaile::iledirection(LaunchDirection));
			//}
			
		}
	}
}

void AYReyna::EyeShotSkill() {
	
	//���� ��ų	
	FHitResult Hit;

	// ����Ʈ���̽��� ĳ���ͷκ��� 1000 ������ ��ġ���� ���󰣴� 
	//  >> 10 ���� 1000������ ������ ������ �� �ֵ��� �ٲ���Ѵ�
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 1000.0f;
	                                                               // 1000�� ȭ�鿡 Ŭ���ϴ� ��ġ��
																   //����Ű�� �Լ��� ������������ ������

	// FCollisionQueryParams
	// ����Ʈ���̽��� ���͸� ���� �ʵ���
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
		                            //�浹����, ������ġ, ������ġ,     ���� ä��,         �浹�ɼ�
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

	//�浹�ϸ� 

	// ����� �� �Ǵ��� Ȯ���ϱ�
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());

	// ����Ʈ���̽��� �浹�ϸ�  bBlockingHit�� true,
	// ������ ġ���� ������ ���̴�.
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{	
		UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}

	

	//����ȿ�� Ʈ������
	FTransform bulletTrans;
	
	//�ε��� ��ġ �Ҵ�
	bulletTrans.SetLocation(Hit.ImpactPoint);
	
	//�Ѿ� ����ȿ�� �ν��Ͻ� ����
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

}

void AYReyna::SilentStep()
{

}

void AYReyna::TelescopeSight() {

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

void AYReyna::WeaponStorageOpen()
{

}