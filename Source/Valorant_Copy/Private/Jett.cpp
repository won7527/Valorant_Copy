// Fill out your copyright notice in the Description page of Project Settings.


#include "Jett.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SmokeGrenade.h"
#include "Knife.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"

// Sets default values
AJett::AJett()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_GUN"));
	FP_Gun->SetOnlyOwnerSee(true);
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AJett::BeginPlay()
{
	Super::BeginPlay();

	const FVector LocationS = GetActorLocation();
	const FRotator RotationS = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(SmokeGrenade, LocationS, RotationS);
	for (TActorIterator<ASmokeGrenade>it(GetWorld()); it; ++it)
	{
		smoke = *it;
	}

	FVector Location = GetActorLocation() + FVector(0, 0, -200);
	DeactivatedLocation = Location;
	FRotator Rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it0(GetWorld()); it0; ++it0)
	{
		knife0 = *it0;
	}
;
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it1(GetWorld()); it1; ++it1)
	{
		
		knife1 = *it1;
	}
	
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it2(GetWorld()); it2; ++it2)
	{
		knife2 = *it2;
	}
	
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it3(GetWorld()); it3; ++it3)
	{
		knife3 = *it3;
	}
	
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it4(GetWorld()); it4; ++it4)
	{
		knife4 = *it4;
	}

	knifeArray.Add(knife0);
	knifeArray.Add(knife1);
	knifeArray.Add(knife2);
	knifeArray.Add(knife3);
	knifeArray.Add(knife4);

}

// Called every frame
void AJett::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DashDir = GetActorForwardVector();

	if (MaxKnife == 5)
	{

		//APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		//FVector camLocation = camManager->GetCameraLocation();
		knife0->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * -200);
		knife1->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * 200);
		knife2->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * -100);
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200);

	}															  
	else if (MaxKnife == 4)
	{
		knife1->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 200);
		knife2->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * -100);
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);
	}
	else if (MaxKnife == 3)
	{
		knife2->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * -100);
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);
	}
	else if (MaxKnife == 2)
	{
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);
	}
	else if (MaxKnife == 1)
	{
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);
	}

	if (isFire) {

		currentTime += DeltaTime;
		if (currentTime > TimeBetweenShots) {
			if (recoilCount < 7) {
				APawn::AddControllerPitchInput(-0.5f);
				recoilCount += 1;

			}
			else if (recoilCount <= 16) {
				APawn::AddControllerYawInput(-1);
				if (recoilCount % 2 == 0) {
					APawn::AddControllerPitchInput(-0.6f);
				}
				else if (recoilCount % 2 == 1) {
					APawn::AddControllerPitchInput(0.3f);
				}

				recoilCount += 1;
			}
			else if (recoilCount <= 25) {
				APawn::AddControllerYawInput(1);

				recoilCount += 1;
			}
			currentTime = 0;
		}

	}

}

// Called to bind functionality to input
void AJett::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJett::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AJett::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AJett::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AJett::Vertical);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AJett::InputJump);
	PlayerInputComponent->BindAction(TEXT("Walking"), IE_Pressed, this, &AJett::Walking);
	PlayerInputComponent->BindAction(TEXT("Walking"), IE_Released, this, &AJett::WalkEnd);
	PlayerInputComponent->BindAction(TEXT("JumpDash"), IE_Pressed, this, &AJett::JumpDash);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &AJett::Dash);
	PlayerInputComponent->BindAction(TEXT("Smoke"), IE_Pressed, this, &AJett::Smoke);
	PlayerInputComponent->BindAction(TEXT("Smoke"), IE_Released, this, &AJett::SmokeControlEnd);
	PlayerInputComponent->BindAction(TEXT("KnifeSet"), IE_Pressed, this, &AJett::KnifeSetting);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AJett::Fire);
	PlayerInputComponent->BindAction(TEXT("FireSp"), IE_Pressed, this, &AJett::FireSp);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AJett::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AJett::StopFire);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AJett::ReloadInput);
	
}

void AJett::Turn(float value)
{
	AddControllerYawInput(value);
}

void AJett::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void AJett::Horizontal(float value)
{
	direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	direction.Normalize();
	AddMovementInput(direction, value);
	//CharacterMoveDir = direction * value;
	//CharacterMoveDir.Z = 0;
	//CharacterMoveDir.Normalize();
	yValue = value;
}

void AJett::Vertical(float value)
{
	
	direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	direction.Normalize();
	AddMovementInput(direction, value);
	//CharacterMoveDir = direction * value;
	//CharacterMoveDir.Z = 0;
	//CharacterMoveDir.Normalize();
	xValue = value;
}

void AJett::InputJump()
{
	Jump();
}

void AJett::Walking()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void AJett::WalkEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = runSpeed;
}

void AJett::JumpDash()
{
	direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Z);
	direction.Normalize();
	LaunchCharacter(direction * jumpdashDistance, true, true);
	
}

void AJett::Dash()
{
	if (xValue == 0 && yValue == 0)
	{
		LaunchCharacter(GetActorForwardVector() * dashDistance, true, true);
	}
	else
	{
		DashDir.X = xValue;
		DashDir.Y = yValue;
		LaunchCharacter(GetActorRotation().RotateVector(DashDir) * dashDistance, true, true);
	}
}


void AJett::Smoke()
{

	smoke->KeepPressed();

}

void AJett::SmokeControlEnd()
{
	
	smoke->ReleasedC();
}


void AJett::KnifeSetting()
{
	if (MaxKnife == 0)
	{
		for (int32 i = 0; i < knifeArray.Num(); i++)
		{
			knifeArray[i]->KnifeDirectionReset();
		}
		MaxKnife = 5;
	}

}

void AJett::Fire()
{
	if (MaxKnife == 5)
	{
		knife0->KnifeThrowing();
		MaxKnife -= 1;

	}
	else if (MaxKnife == 4)
	{
		knife1->KnifeThrowing();
		MaxKnife -= 1;
	}
	else if (MaxKnife == 3)
	{
		knife2->KnifeThrowing();
		MaxKnife -= 1;
	}
	else if (MaxKnife == 2)
	{
		knife3->KnifeThrowing();
		MaxKnife -= 1;
	}
	else if (MaxKnife == 1)
	{
		knife4->KnifeThrowing();
		MaxKnife -= 1;
	}

}

void AJett::FireSp()
{

	if (MaxKnife == 5)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(KnifeTime, this, &AJett::Fire, 0.2f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime1, this, &AJett::Fire, 0.4f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime2, this, &AJett::Fire, 0.6f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime3, this, &AJett::Fire, 0.8f, false);
	
	}
	else if (MaxKnife == 4)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(KnifeTime, this, &AJett::Fire, 0.2f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime1, this, &AJett::Fire, 0.4f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime2, this, &AJett::Fire, 0.6f, false);
	}
	else if (MaxKnife == 3)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(KnifeTime, this, &AJett::Fire, 0.2f, false);
		GetWorld()->GetTimerManager().SetTimer(KnifeTime1, this, &AJett::Fire, 0.4f, false);
	}

	else if (MaxKnife == 2)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(KnifeTime, this, &AJett::Fire, 0.2f, false);
	}
	else if (MaxKnife == 1)
	{
		Fire();
	}

}


void AJett::StartFire()
{
	//rebound = FVector(0,0,0);
	//rebound = FireShot(rebound);
	if (ammunition > 0) {
		isFire = true;
		GetWorldTimerManager().SetTimer(TimerHandle_HandleRefire, this, &AJett::FireShot, TimeBetweenShots, true);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("no ammo")));
	}

}

void AJett::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_HandleRefire);
	rebound = FVector(0, 0, 0);
	recoilCount = 0;
	reboundCount = 0;
	YDir = FVector(0, 0, 0);
	ZDir = FVector(0, 0, 0);
	isFire = false;
}

void AJett::FireShot()
{
	FHitResult Hit;

	//총의 탄퍼짐은 EndTrace로 조정
	//일정 패턴은 카메라 움직임으로 조정

	//카메라를 위로 올리는 반동
	//CamPitch = FirstPersonCameraComponent->GetRelativeRotation() + FRotator(10.0f, 0, 0);
	//FirstPersonCameraComponent->SetRelativeRotation(CamPitch);

	//총이 나가는 위치를 올리는 반동

	/*if (reboundCount <= 7) {
		reZ += FMath::RandRange(0.01f, 0.03f);
		rebound += FVector(0, 0, reZ);
		reboundCount++;
	}*/
	if (reboundCount == 7) {
		reboundOrigin = rebound;
	}

	//7발 까지는 패턴이 일정하다
	switch (reboundCount) {
	case 0:
		YDir = FirstPersonCameraComponent->GetRightVector() * 0;
		rebound *= 0;
		reboundCount++;
		break;
	case 1:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(-0.01f, 0.01f);
		rebound.Z += FMath::RandRange(0.005f, 0.01f);
		reboundCount++;
		break;
	case 2:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(-0.01f, 0.01f);
		rebound.Z += FMath::RandRange(0.005f, 0.01f);
		reboundCount++;
		break;
	case 3:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.01f, 0.17f);
		rebound.Z += FMath::RandRange(0.05f, 0.06f);
		reboundCount++;
		break;
	case 4:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.01f, 0.02f);
		rebound.Z += FMath::RandRange(0.05f, 0.06f);
		reboundCount++;
		break;
	case 5:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.02f, 0.03f);
		rebound.Z += FMath::RandRange(0.05f, 0.06f);
		reboundCount++;
		break;
	case 6:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.03f, 0.04f);
		rebound.Z += FMath::RandRange(0.05f, 0.06f);
		reboundCount++;
		break;
	}
	if (reboundCount > 6) {
		//rebound = reboundOrigin;
		//reX = FMath::RandRange(0.1, 0.3);
		reY = FMath::RandRange(-0.05f, 0.05f);
		reZ = FMath::RandRange(-0.05f, 0.05f);
		YDir = FirstPersonCameraComponent->GetRightVector() * reY;
		ZDir = FirstPersonCameraComponent->GetUpVector() * reZ;
		//rebound+=FVector(reX, reY, reZ);
		reboundCount++;
	}

	const float WeaponRange = 20000.0f;
	const FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	const FVector EndTrace = (((FirstPersonCameraComponent->GetForwardVector() + rebound) + YDir + ZDir) * WeaponRange) + StartTrace;

	FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams)) {

		if (ImpactParticles) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));
			//데미지 이벤트
			ShotDirection = FirstPersonCameraComponent->GetForwardVector();
			ShotDirection.Normalize();

			//FDamageEvent dam;
			//FPointDamageEvent fdm;

			//FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

			//AActor* HitActor = Hit.GetActor();
			//if (HitActor != nullptr) {
			//	HitActor->TakeDamage(Damage, DamageEvent);
			// }
		}

	}

	if (MuzzleParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticles, FP_Gun->GetSocketTransform(FName("Muzzle")));
	}

	if (FireSound != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation != nullptr) {

		UAnimInstance* Animinstance = Mesh1P->GetAnimInstance();
		if (Animinstance != nullptr) {
			Animinstance->Montage_Play(FireAnimation, 1.f);
		}
	}


	//탄약이 0 이되면 사격종료
	ammunition--;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" %d, isFrie? = %d"), ammunition, isFire));

	if (ammunition <= 0) {
		StopFire();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("no ammo")));
	}

}

void AJett::ReloadInput() {
	if (isFire == false) {
		GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AJett::Reload, TimeReload, false);
	}
}

void AJett::Reload()
{
	ammunition = 25;
}

int32 AJett::GetAmmo()
{
	return ammunition;
}
