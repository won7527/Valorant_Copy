// Fill out your copyright notice in the Description page of Project Settings.


#include "ValEnemy.h"
#include "FSM.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Jett.h"
#include "EngineUtils.h"
#include "Knife.h"
#include "Jett.h"
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
}

// Called when the game starts or when spawned
void AValEnemy::BeginPlay()
{
	Super::BeginPlay();


	HP = 5;
}

// Called every frame
void AValEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
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

// Called to bind functionality to input
void AValEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AValEnemy::Fire()
{
	FHitResult Hit;
	FVector StartTrace = GetActorLocation();
	for (TActorIterator<AJett>jett(GetWorld()); jett; ++jett)
	{
		Jett = *jett;
	}

	FVector EndTrace = GetActorForwardVector()+20000.0f+StartTrace;

	FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams))
	{

		if (ImpactParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));
		}

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
	if (jett) {
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AValorant* myGM = Cast<AValorant>(gm);
		myGM->Damaged(5);
		UE_LOG(LogTemp, Warning, TEXT("playerHit"));
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
	UE_LOG(LogTemp, Warning, TEXT("HIT"));
	if (HP == 0)
	{
		this->Destroy();
	}
}
