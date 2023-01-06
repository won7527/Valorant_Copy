// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Animation/AnimInstance.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	SetRootComponent(boxComp);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	mesh->SetupAttachment(RootComponent);

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_GUN"));
	FP_Gun->SetOnlyOwnerSee(true);
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::EnemyFire()
{

	//FHitResult Hit;

	//const FVector StartTrace = FP_Gun->GetComponentLocation();
	//const FVector EndTrace = 
	//
	//if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, SniperEndTrace, ECC_Visibility, SniperQueryParams)) {

	//	if (SniperImpactParticles) {
	//		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SniperImpactParticles, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));

	//		//if (GEngine)
	//			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("shots")));
	//	}

	//}

	//if (SniperMuzzleParticles) {
	//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SniperMuzzleParticles, FP_Snipergun->GetSocketTransform(FName("Muzzle")));
	//}

	//if (SniperSound != nullptr) {
	//	UGameplayStatics::PlaySoundAtLocation(this, SniperSound, GetActorLocation());
	//}
}

