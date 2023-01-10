// Fill out your copyright notice in the Description page of Project Settings.


#include "ValEnemy.h"
#include "FSM.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Jett.h"
#include "EngineUtils.h"
#include "Knife.h"
#include "Components/StaticMeshComponent.h"
#include "Valorant.h"


// Sets default values
AValEnemy::AValEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_GUN"));
	FP_Gun->SetOnlyOwnerSee(false);
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

	fsm = CreateDefaultSubobject<UFSM>(TEXT("FSM"));

	HPRed = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RED"));
	HPBlack = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Black"));
	
	HPRed->SetupAttachment(RootComponent);
	HPBlack->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AValEnemy::BeginPlay()
{
	Super::BeginPlay();

	MaxHp = 10;
	HP = MaxHp;
	HPRate = 1/MaxHp;
}

// Called every frame
void AValEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (enemyMoveSet == true) {

		if (ismove == true) {

			cur += DeltaTime;
			if (isturn == false) {
				if (cur < 1.5) {
					AddMovementInput(GetActorForwardVector());

				}
				else {
					isturn = true;
					cur = 0;
					SetActorRotation(GetActorRotation() - FRotator(0, -180, 0));
				}
			}
			if (isturn == true)
			{
				if (cur < 1.5)
				{
					AddMovementInput(GetActorForwardVector());
				}
				else {
					isturn = false;
					cur = 0;
					SetActorRotation(GetActorRotation() - FRotator(0, -180, 0));
				}
			}

		}

	}
	for (int i = 0; i < 5; i++) {

		FVector StartTrace = GetActorLocation();

		FVector sightDetectRangeTotalVec = GetActorRightVector() * (-0.5 * sightDetectRange * 4);
		FVector sightDetectRangeVec = GetActorRightVector() * (sightDetectRange * i);

		FVector EndTrace = (GetActorForwardVector() + sightDetectRangeTotalVec + sightDetectRangeVec) * 5000.0f + StartTrace;
		FCollisionQueryParams EQueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);
		GetWorld()->LineTraceSingleByChannel(Hit_detect, StartTrace, EndTrace, ECC_Visibility, EQueryParams);

		//when player detacted
		AJett* jett = Cast<AJett>(Hit_detect.GetActor());
		if (jett!=nullptr) {
			isPlayerDetected = true;
			/*if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("detect")));*/
			break;
		}
		else {
			isPlayerDetected = false;
			/*if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("not")));*/

		}
	}

}

// Called to bind functionality to input
void AValEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AValEnemy::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("sdsd"));
	FHitResult Hit;
	FVector StartTrace = FP_Gun->GetComponentLocation();
	for (TActorIterator<AJett>jett(GetWorld()); jett; ++jett)
	{
		Jett = *jett;
	}

	FVector EndTrace = Jett->GetActorLocation();//FP_Gun->GetForwardVector() + 20000.0f + StartTrace;

	FCollisionQueryParams EQueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, EQueryParams))
	{

		if (ImpactParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));
		}
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.GetActor()->GetName());

	}

	if (MuzzleParticles) 
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticles, FP_Gun->GetSocketTransform(FName("Muzzle")));
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation != nullptr)
	{
		
	}

	AJett* jett = Cast<AJett>(Hit.GetActor());
	if (jett!=nullptr) {
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AValorant* myGM = Cast<AValorant>(gm);
		if (myGM != nullptr) {
			myGM->Damaged(5);
		}
		//UE_LOG(LogTemp, Warning, TEXT("playerHit"));
	}

	isDelay = true;
}

void AValEnemy::FireDelay()
{
	if (!isDelay)
	{
		Fire();
		GetWorld()->GetTimerManager().SetTimer(cooltime, this, &AValEnemy::FireDelayEnd, 1.0f, false);
	}
}

void AValEnemy::FireDelayEnd()
{
	isDelay = false;
}

void AValEnemy::Attacked(int32 deal)
{
	HP -= deal;
	HPRed->SetRelativeScale3D(FVector(0.1, HPRate * HP, 0.1));
	HPBlack->SetRelativeScale3D(FVector(0.1, 1 - HPRate * HP, 0.1));
	HPRed->SetRelativeLocation(FVector(0, 50 * HPRate * (MaxHp - HP), 120));
	HPBlack->SetRelativeLocation(FVector(0, -50 * HPRate * (HP), 120));
	


	if (HP <= 0)
	{
		if (DeathParticles != nullptr) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticles, GetActorLocation());
		}
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AValorant* myGM = Cast<AValorant>(gm);
		if (myGM != nullptr) {

			myGM->enemyNum--;
			//when enemy all Destroy = round win
			if (myGM->enemyNum <= 0) {
				EnemyAllDestory();
			}
			myGM->Money += 500;
			myGM->UpMoney();
			this->Destroy();
		}
	}
}

void AValEnemy::EnemyAllDestory()
{
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AValorant* myGM = Cast<AValorant>(gm);
	if (myGM != nullptr) {
		//widget print
		myGM->RWinWidgetPrint();
		//restart delay
		FTimerHandle TimerHandle_win;
		GetWorldTimerManager().SetTimer(TimerHandle_win, myGM, &AValorant::WinRound, 2.5f, false);
	}
}
