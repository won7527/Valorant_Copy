// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGun::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AGun::Vertical);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AGun::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AGun::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &AGun::StopFire);



}

void AGun::StartFire()
{
}

void AGun::StopFire()
{
}

void AGun::FireShot()
{
}

void AGun::Vertical(float AxisValue) {
	//direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//direction.Normalize();
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AGun::Horizontal(float AxisValue) {
	AddMovementInput(GetActorRightVector() * AxisValue);
}
