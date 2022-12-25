// Fill out your copyright notice in the Description page of Project Settings.


#include "Jett.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SmokeGrenade.h"
#include "Knife.h"

// Sets default values
AJett::AJett()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AJett::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 4; i < 5; i++)
	{
		const FVector Location = GetActorLocation();
		const FRotator Rotation = GetActorRotation();
		GetWorld()->SpawnActor<AActor>(SmokeGrenade, Location, Rotation);
	}
}

// Called every frame
void AJett::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

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
	PlayerInputComponent->BindAction(TEXT("KnifeThrow"), IE_Pressed, this, &AJett::KnifeThrow);
	
	

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
	AddMovementInput(direction, value);
	
}

void AJett::Vertical(float value)
{
	
	direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, value);
	
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
	LaunchCharacter(direction * jumpdashDistance, true, true);
}

void AJett::Dash()
{
	
	LaunchCharacter(direction * dashDistance, true, true);
}

void AJett::Smoke()
{
	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(SmokeGrenade, Location, Rotation);
}

void AJett::KnifeThrow()
{
	if (MaxKnife == 0)
	{
		for (int32 i = 0; i < 5; i++)
		{
		
		}
	}
	else
	{
		//Knife::KnifeThrowing;
	}
}