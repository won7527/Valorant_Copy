// Fill out your copyright notice in the Description page of Project Settings.


#include "SmokeGrenade.h"


// Sets default values
ASmokeGrenade::ASmokeGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASmokeGrenade::BeginPlay()
{
	Super::BeginPlay();

	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	//FVector camLocation = camManager->GetCameraLocation();
	FVector camForward = camManager->GetCameraRotation().Vector();

	direction = camForward;

	
}

// Called every frame
void ASmokeGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
}

