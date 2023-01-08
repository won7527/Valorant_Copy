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
#include "ValEnemy.h"
#include "Valorant.h"
#include "Enemy.h"

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

	//���� ����
	FP_Shotgun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Shotgun"));
	FP_Shotgun->SetOnlyOwnerSee(true);
	FP_Shotgun->bCastDynamicShadow = false;
	FP_Shotgun->CastShadow = false;
	FP_Shotgun->SetupAttachment(RootComponent);

	//���� ����
	FP_Snipergun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Sniper"));
	FP_Snipergun->SetOnlyOwnerSee(true);
	FP_Snipergun->bCastDynamicShadow = false;
	FP_Snipergun->CastShadow = false;
	FP_Snipergun->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AJett::BeginPlay()
{
	Super::BeginPlay();

	Weapon1Use();


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

	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("isPlayerMakingSound : %d"), isPlayerMakingSound));*/

	//player location check
	if (isBefore == true) {
		BeforeVec = GetActorLocation();
		isBefore = false;
	}
	else if (isBefore == false) {
		AfterVec = GetActorLocation();
		isBefore = true;
	}

	if (BeforeVec == AfterVec) {
		isPlayerMoving = false;
		/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("same")));*/
	}
	else {
		isPlayerMoving = true;
		/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("ddd")));*/
	}
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("before : %s, after : %s"), *BeforeVec.ToString(), *AfterVec.ToString()));*/

	//footSound
	
	if (isWalking == false) {
		//when pressed anykey
		if (isPA || isPD || isPW || isPS) {
			// A and D or W and S is don't pressed sameTime or ADW, ADS, WSA, WSD pressed sameTime can go 
			if ((!((isPA && isPD) || (isPW && isPS))) || ((isPA && isPD && isPW) || (isPA && isPD && isPS) || (isPW && isPS && isPA) || (isPW && isPS && isPD))) {

				FootSoundInitial += DeltaTime;
				if (FootSoundInitial >= FootSoundDelay) {

					if (footSound != nullptr) {

						UGameplayStatics::PlaySoundAtLocation(this, footSound, GetActorLocation());

					}

					FootSoundInitial = 0;
					isPlayerMakingSound = true;
				}

			}
			else if (isFire == true || isShotgunDelay == true || isSniperDelay == true) {
				isPlayerMakingSound = true;
			}
			else {
				isPlayerMakingSound = false;
			}

		}
		else if (isFire == true || isShotgunDelay == true || isSniperDelay == true) {
			isPlayerMakingSound = true;
		}
		else {
			isPlayerMakingSound = false;
		}

	}
	else if (isFire == true || isShotgunDelay == true || isSniperDelay == true) {
		isPlayerMakingSound = true;
	}
	else {
		isPlayerMakingSound = false;
	}



	DashDir = GetActorForwardVector();

	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FRotator camRotation = camManager->GetCameraRotation();

	if (MaxKnife == 5)
	{

		//APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		//FVector camLocation = camManager->GetCameraLocation();

		knife0->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * -200);
		knife1->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * 200);
		knife2->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * -100);
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector()* 200);

		knife0->SetActorRotation(camRotation);
		knife1->SetActorRotation(camRotation);
		knife2->SetActorRotation(camRotation);
		knife3->SetActorRotation(camRotation);
		knife4->SetActorRotation(camRotation);

	}															  
	else if (MaxKnife == 4)
	{
		knife1->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 200);
		knife2->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * -100);
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);

		knife1->SetActorRotation(camRotation);
		knife2->SetActorRotation(camRotation);
		knife3->SetActorRotation(camRotation);
		knife4->SetActorRotation(camRotation);
	}
	else if (MaxKnife == 3)
	{
		knife2->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * -100);
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);

		knife2->SetActorRotation(camRotation);
		knife3->SetActorRotation(camRotation);
		knife4->SetActorRotation(camRotation);
	}
	else if (MaxKnife == 2)
	{
		knife3->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200 + GetActorRightVector() * 100);
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);

		knife3->SetActorRotation(camRotation);
		knife4->SetActorRotation(camRotation);
	}
	else if (MaxKnife == 1)
	{
		knife4->SetActorLocation(GetActorLocation() + GetActorForwardVector() * 200);

		knife4->SetActorRotation(camRotation);
	}

	if (isFire) {

		currentTime += DeltaTime;
		if (currentTime >= TimeBetweenShots) {
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
	PlayerInputComponent->BindAction(TEXT("InputJump"), IE_Pressed, this, &AJett::InputJump);
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
	//���� ��ü
	PlayerInputComponent->BindAction(TEXT("Weapon1"), IE_Pressed, this, &AJett::Weapon1Use);
	PlayerInputComponent->BindAction(TEXT("Weapon2"), IE_Pressed, this, &AJett::Weapon2Use);
	PlayerInputComponent->BindAction(TEXT("Weapon3"), IE_Pressed, this, &AJett::Weapon3Use);
	//����
	PlayerInputComponent->BindAction(TEXT("FireSp"), IE_Pressed, this, &AJett::SniperAim);
	PlayerInputComponent->BindAction(TEXT("FireSp"), IE_Released, this, &AJett::SniperAim);

	//sound When Pressed
	PlayerInputComponent->BindAction(TEXT("A"), IE_Pressed, this, &AJett::PressedA);
	PlayerInputComponent->BindAction(TEXT("D"), IE_Pressed, this, &AJett::PressedD);
	PlayerInputComponent->BindAction(TEXT("W"), IE_Pressed, this, &AJett::PressedW);
	PlayerInputComponent->BindAction(TEXT("S"), IE_Pressed, this, &AJett::PressedS);
	//sound when released
	PlayerInputComponent->BindAction(TEXT("A"), IE_Released, this, &AJett::ReleasedA);
	PlayerInputComponent->BindAction(TEXT("D"), IE_Released, this, &AJett::ReleasedD);
	PlayerInputComponent->BindAction(TEXT("W"), IE_Released, this, &AJett::ReleasedW);
	PlayerInputComponent->BindAction(TEXT("S"), IE_Released, this, &AJett::ReleasedS);

	//buysreen
	PlayerInputComponent->BindAction(TEXT("Buy"), IE_Pressed, this, &AJett::PressBuy);
	PlayerInputComponent->BindAction(TEXT("Buy"), IE_Released, this, &AJett::ReleaseBuy);

	
}

void AJett::Turn(float value)
{
	if (isOnSreen == true) {
		value = 0;
	}
	AddControllerYawInput(value);
}

void AJett::LookUp(float value)
{
	if (isOnSreen == true) {
		value = 0;
	}
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

void AJett::PressedA()
{
	isPA = true;
}

void AJett::ReleasedA()
{
	isPA = false;
}

void AJett::PressedD()
{
	isPD = true;
}

void AJett::ReleasedD()
{
	isPD = false;
}

void AJett::PressedW()
{
	isPW = true;
}

void AJett::ReleasedW()
{
	isPW = false;
}

void AJett::PressedS()
{
	isPS = true;
}

void AJett::ReleasedS()
{
	isPS = false;
}

void AJett::InputJump()
{
	Jump();
}

void AJett::Walking()
{
	//when iswalking true no footSound
	isWalking = true;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void AJett::WalkEnd()
{
	////when iswalking false footSound
	isWalking = false;
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
	const FVector LocationS = GetActorLocation();
	const FRotator RotationS = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(SmokeGrenade, LocationS, RotationS);
	for (TActorIterator<ASmokeGrenade>it(GetWorld()); it; ++it)
	{
		smoke = *it;
	}
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

void AJett::PressBuy()
{
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	myGM = Cast<AValorant>(gm);
	if (myGM != nullptr) {
		myGM->PrintBuy();
	}
}

void AJett::ReleaseBuy()
{
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	myGM = Cast<AValorant>(gm);
	if (myGM != nullptr) {
		myGM->RemoveBuy();
	}
}


void AJett::StartFire()
{
	//rebound = FVector(0,0,0);
	//rebound = FireShot(rebound);
	if(MaxKnife == 0)
	{ 
		if (isWeapon1Use == true) {

			if (ammunition >= 1) {
				isFire = true;
				FireShot();
				isPlayerMakingSound = true;
				//when ammo is 1 can't fire twice
				if (ammunition >= 2) {
					GetWorldTimerManager().SetTimer(TimerHandle_HandleRefire, this, &AJett::FireShot, TimeBetweenShots, true, TimeBetweenShots);
				}
			}

		}
	

		if (isWeapon2Use == true) {

			if (shotgunAmmo > 0) {

				if (isShotgunDelay == false) {

					//����� �����ϸ� ������ �����
					GetWorldTimerManager().ClearTimer(TimerHandle_ShotgunReload);

					for (int i = 0; i < pellet; i++) {
						FHitResult Hit;
						const float ShotgunRange = 20000.0f;
						const FVector ShotgunStartTrace = FirstPersonCameraComponent->GetComponentLocation();

						//������ �� �Ÿ�
						//FVector totalSpace = FirstPersonCameraComponent->GetRightVector()*(- 0.5 * (pellet - 1) * 0.1f);
						//FVector space = FirstPersonCameraComponent->GetRightVector() * (0.1f * i);

						float yRand = FMath::RandRange(-0.02f*i, 0.02f*i);
						float ZRand = FMath::RandRange(-0.02f*i, 0.02f*i);
						FVector Y = FirstPersonCameraComponent->GetRightVector() * yRand;
						FVector Z = FirstPersonCameraComponent->GetUpVector() * ZRand;

						const FVector ShotgunEndTrace = ((FirstPersonCameraComponent->GetForwardVector()+Y+Z) * ShotgunRange) + ShotgunStartTrace;

						FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);

						if (GetWorld()->LineTraceSingleByChannel(Hit, ShotgunStartTrace, ShotgunEndTrace, ECC_Visibility, QueryParams)) {

							if (ShotgunImpactParticles) {
								UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShotgunImpactParticles, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));

								//if (GEngine)
									//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("shots")));
							}
				
						}
						AValEnemy* enemy = Cast<AValEnemy>(Hit.GetActor());
						if (enemy!=nullptr)
						{
							enemy->Attacked(2);
						}
		
					}

					if (ShotgunMuzzleParticles) {
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShotgunMuzzleParticles, FP_Shotgun->GetSocketTransform(FName("Muzzle")));
					}

					if (ShotgunSound != nullptr) {
						UGameplayStatics::PlaySoundAtLocation(this, ShotgunSound, GetActorLocation());
					}
					//ź�� �Һ��Ѵ�
					shotgunAmmo--;

					//���� ź�Ҹ� ���Ӹ�忡 �˸���
					AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
					myGM = Cast<AValorant>(gm);
					myGM->ShotgunMinusAmmo();
					//�ݵ�
					APawn::AddControllerPitchInput(-1.2f);
					APawn::AddControllerYawInput(-0.5f);

					isShotgunDelay = true;
					isPlayerMakingSound = true;
					GetWorldTimerManager().SetTimer(TimerHandle_ShotgunDelay, this, &AJett::ShotgunDelay, 1.0f, false);


				
				}

			}

		}
		if (isWeapon3Use == true) {


			if (sniperAmmo > 0) {

				if (isSniperDelay == false) {
					//scope
					AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
					myGM = Cast<AValorant>(gm);
					if (myGM->isScope == false) {
						sniperScopeCoef = 0.1f;
					}
					else {
						sniperScopeCoef = 0;
					}
					//move
					if (isPlayerMoving == true) {
						movingCoef = 0.1f;
					}
					else
					{
						movingCoef = 0;
					}
					FVector randomVec = FVector(0, FMath::RandRange(-sniperScopeCoef-movingCoef, sniperScopeCoef+movingCoef), FMath::RandRange(-sniperScopeCoef-movingCoef, sniperScopeCoef+movingCoef));
					FHitResult Hit;
					const float SniperRange = 20000.0f;
					const FVector SniperStartTrace = FirstPersonCameraComponent->GetComponentLocation();

					//��������
					const FVector SniperEndTrace = (FirstPersonCameraComponent->GetForwardVector()+randomVec)*SniperRange+SniperStartTrace;

					FCollisionQueryParams SniperQueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);

					if (GetWorld()->LineTraceSingleByChannel(Hit, SniperStartTrace, SniperEndTrace, ECC_Visibility, SniperQueryParams)) {

						if (SniperImpactParticles) {
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SniperImpactParticles, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));

							//if (GEngine)
									//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("shots")));
						}

					}

					if (SniperMuzzleParticles) {
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SniperMuzzleParticles, FP_Snipergun->GetSocketTransform(FName("Muzzle")));
					}

					if (SniperSound != nullptr) {
						UGameplayStatics::PlaySoundAtLocation(this, SniperSound, GetActorLocation());
					}

					sniperAmmo--;
					myGM->SniperMinusAmmo();

					APawn::AddControllerPitchInput(-2.0f);
					//APawn::AddControllerYawInput(-0.0f);
					/*class AEnemy* enemy = Cast<AEnemy>(Hit.GetActor());
					if (enemy) {
						if (GEngine)
							GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("E hit")));
					}*/

					//sniper delay
					isSniperDelay = true;
					isPlayerMakingSound = true;
					GetWorldTimerManager().SetTimer(TimerHandle_SniperDelay, this, &AJett::SniperDelay, SniperDelayTime, false);

					AValEnemy* enemy = Cast<AValEnemy>(Hit.GetActor());
					if (enemy!=nullptr)
					{
						enemy->Attacked(10);
					}


				}


			}


		}
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
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
	isPlayerMakingSound = false;
}

void AJett::FireShot()
{
	FHitResult Hit;

	if (isPlayerMoving == true) {
		movingCoef = 0.1f;
		movingOver6Coef = 0.05f;
	}
	else {
		movingCoef = 0;
		movingOver6Coef = 0;
	}
	//���� ź������ EndTrace�� ����
	//���� ������ ī�޶� ���������� ����

	//ī�޶� ���� �ø��� �ݵ�
	//CamPitch = FirstPersonCameraComponent->GetRelativeRotation() + FRotator(10.0f, 0, 0);
	//FirstPersonCameraComponent->SetRelativeRotation(CamPitch);

	//���� ������ ��ġ�� �ø��� �ݵ�

	/*if (reboundCount <= 7) {
		reZ += FMath::RandRange(0.01f, 0.03f);
		rebound += FVector(0, 0, reZ);
		reboundCount++;
	}*/
	if (reboundCount == 7) {
		reboundOrigin = rebound;
	}

	//horizontal camera vertical bullet
	switch (reboundCount) {
	case 0:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(-movingCoef, movingCoef);
		rebound.Z += FMath::RandRange(-movingCoef, movingCoef);
		reboundCount++;
		break;
	case 1:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(-0.01f - movingCoef, 0.01f + movingCoef);
		rebound.Z += FMath::RandRange(0.005f - movingCoef, 0.01f + movingCoef);
		reboundCount++;
		break;
	case 2:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(-0.01f - movingCoef, 0.01f + movingCoef);
		rebound.Z += FMath::RandRange(0.005f - movingCoef, 0.01f + movingCoef);
		reboundCount++;
		break;
	case 3:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.01f - movingCoef, 0.17f+ movingCoef);
		rebound.Z += FMath::RandRange(0.05f- movingCoef, 0.06f+ movingCoef);
		reboundCount++;
		break;
	case 4:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.01f- movingCoef, 0.02f+ movingCoef);
		rebound.Z += FMath::RandRange(0.05f- movingCoef, 0.06f+ movingCoef);
		reboundCount++;
		break;
	case 5:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.02f- movingCoef, 0.03f+ movingCoef);
		rebound.Z += FMath::RandRange(0.05f- movingCoef, 0.06f+ movingCoef);
		reboundCount++;
		break;
	case 6:
		YDir = FirstPersonCameraComponent->GetRightVector() * FMath::RandRange(0.03f- movingCoef, 0.04f+ movingCoef);
		rebound.Z += FMath::RandRange(0.05f- movingCoef, 0.06f+ movingCoef);
		reboundCount++;
		break;
	}
	if (reboundCount > 6) {
		//rebound = reboundOrigin;
		//reX = FMath::RandRange(0.1, 0.3);
		reY = FMath::RandRange(-0.05f- movingOver6Coef, 0.05f+ movingOver6Coef);
		reZ = FMath::RandRange(-0.05f- movingOver6Coef, 0.05f+ movingOver6Coef);
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
			//������ �̺�Ʈ
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

	//맞은 타겟과의 거리계산
	FVector distance = FirstPersonCameraComponent->GetComponentLocation() - Hit.ImpactPoint;

	AValEnemy* enemy = Cast<AValEnemy>(Hit.GetActor());
	if (enemy!=nullptr)
	{
		if (distance.Size() < 500.0f) {
			enemy->Attacked(3);
		}
		else {
			enemy->Attacked(1);
		}
	}


	//ź���� 0 �̵Ǹ� �������
	ammunition--;

	//ź�Ҹ� ���Ӹ�忡 �˸���
	AGameModeBase* gm =  UGameplayStatics::GetGameMode(this);
	myGM = Cast<AValorant>(gm);
	myGM->MinusAmmo(1);
	UE_LOG(LogTemp, Warning, TEXT("%d"), myGM->GetAmmo());

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(" %d, isFrie? = %d"), ammunition, isFire));

	if (ammunition <= 0) {
		StopFire();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("no ammo")));
	}

}

void AJett::ReloadInput() {
	if (isWeapon1Use == true) {
		if (isFire == false) {
			if (AKReloadingSound != nullptr) {
				UGameplayStatics::PlaySoundAtLocation(this, AKReloadingSound, GetActorLocation());
			}
			GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AJett::Reload, TimeReload, false);
		}
	}

	if (isWeapon2Use == true) {
		
		GetWorldTimerManager().SetTimer(TimerHandle_ShotgunReload, this, &AJett::ShotgunReload, ShotgunTimeReload, true);
		
	}

	if (isWeapon3Use == true) {
		if (SniperReloadingSound != nullptr) {
			UGameplayStatics::PlaySoundAtLocation(this, SniperReloadingSound, GetActorLocation());
		}
		GetWorldTimerManager().SetTimer(TimerHandle_Reload, this, &AJett::SniperReload, SniperTimeReload, false);
	}
}

void AJett::Reload()
{
	if (ammunition <= 24) {
		ammunition = 25;
		//�����Ҷ����� ������ ������Ʈ�� �Ѵ�
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		myGM = Cast<AValorant>(gm);
		myGM->ReloadAmmo();

	}
}

void AJett::ShotgunReload()
{
	if (shotgunAmmo < maxShotgunAmmo) {
		if (ShotgunReloadingSound != nullptr) {
			UGameplayStatics::PlaySoundAtLocation(this, ShotgunReloadingSound, GetActorLocation());
		}
		shotgunAmmo += 1;
		//������ ���Ӹ�忡 �˸���
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		myGM = Cast<AValorant>(gm);
		myGM->ShotgunReloadAmmo();
		/*if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("reload")));*/

	}
	else if (shotgunAmmo >= maxShotgunAmmo) {
		GetWorldTimerManager().ClearTimer(TimerHandle_ShotgunReload);
	}
}

void AJett::SniperReload()
{
	if (sniperAmmo <= 4) {

		sniperAmmo = 5;
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		myGM = Cast<AValorant>(gm);
		myGM->SniperReloadAmmo();

	}
}

void AJett::ShotgunDelay()
{
	isShotgunDelay = false;
	isPlayerMakingSound = false;
}

int32 AJett::GetAmmo()
{
	return ammunition;
}

void AJett::Weapon1Use()
{
	isWeapon1Use = true;
	isWeapon2Use = false;
	isWeapon3Use = false;
	FP_Shotgun->SetVisibility(false);
	FP_Gun->SetVisibility(true);
	FP_Snipergun->SetVisibility(false);
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	myGM = Cast<AValorant>(gm);
	myGM->ChangeWeapon();
}

void AJett::Weapon2Use()
{
	isWeapon1Use = false;
	isWeapon2Use = true;
	isWeapon3Use = false;
	FP_Shotgun->SetVisibility(true);
	FP_Gun->SetVisibility(false);
	FP_Snipergun->SetVisibility(false);
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	myGM = Cast<AValorant>(gm);
	myGM->ChangeWeapon();
}

void AJett::Weapon3Use()
{
	isWeapon1Use = false;
	isWeapon2Use = false;
	isWeapon3Use = true;
	FP_Shotgun->SetVisibility(false);
	FP_Gun->SetVisibility(false);
	FP_Snipergun->SetVisibility(true);
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	myGM = Cast<AValorant>(gm);
	myGM->ChangeWeapon();
}

void AJett::SniperAim()
{
	if (isWeapon3Use == true) {
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		myGM = Cast<AValorant>(gm);
		if (myGM != nullptr) {

			myGM->SniperAimMod();
			if (myGM->isScope == true) {
				FirstPersonCameraComponent->SetFieldOfView(20.0f);
			}
			else
				FirstPersonCameraComponent->SetFieldOfView(90.0f);
		}
		
	}
}

void AJett::SniperDelay()
{
	isSniperDelay = false;
	isPlayerMakingSound = false;
}

