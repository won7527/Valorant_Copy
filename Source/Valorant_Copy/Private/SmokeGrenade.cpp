// Fill out your copyright notice in the Description page of Project Settings.


#include "SmokeGrenade.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASmokeGrenade::ASmokeGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	sphComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphere"));
	SetRootComponent(sphComp);
	sphComp->SetSphereRadius(50.0);
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	meshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ASmokeGrenade::BeginPlay()
{
	Super::BeginPlay();

	sphComp->OnComponentBeginOverlap.AddDynamic(this, &ASmokeGrenade::OnOverlap);
}

// Called every frame
void ASmokeGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (keepPressed)
	{
		APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		FVector camForward = camManager->GetCameraRotation().Vector();
		direction = camForward;
	}
	if (!isOverlap)
	{
		time += DeltaTime;
	}

	SetActorLocation(GetActorLocation() + initS * direction - FVector(0, 0, 1) * 1.5 * time);

	SetActorRotation(GetActorRotation() + FRotator(0, 10, 10));
}

void ASmokeGrenade::KeepPressed()
{
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector camForward = camManager->GetCameraRotation().Vector();
	direction = camForward;
	keepPressed = true;
}

void ASmokeGrenade::ReleasedC()
{
	keepPressed = false;
	
}

void ASmokeGrenade::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	sphComp->SetRelativeScale3D(FVector(5, 5, 5));
	initS = 0;
	isOverlap = true;
	time = 0;
	FTimerHandle smokeexist;
	GetWorld()->GetTimerManager().SetTimer(smokeexist, this, &ASmokeGrenade::DestroySmoke, 3, true);

}

void ASmokeGrenade::DestroySmoke()
{
	this->Destroy();
}