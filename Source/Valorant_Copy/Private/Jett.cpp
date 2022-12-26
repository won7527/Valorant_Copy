// Fill out your copyright notice in the Description page of Project Settings.


#include "Jett.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SmokeGrenade.h"
#include "Knife.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

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
	
	FVector Location = GetActorLocation() + (100, 0, 0);
	DeactivatedLocation = Location;
	FRotator Rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it0(GetWorld()); it0; ++it0)
	{
		knife0 = *it0;
	}
	FVector Location1 = GetActorLocation() + (10, 0, 0);
	FRotator Rotation1 = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it1(GetWorld()); it1; ++it1)
	{
		
		knife1 = *it1;
	}
	FVector Location2 = GetActorLocation() + (10, 0, 0);
	FRotator Rotation2 = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it2(GetWorld()); it2; ++it2)
	{
		knife2 = *it2;
	}
	FVector Location3 = GetActorLocation() + (10, 0, 0);
	FRotator Rotation3 = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it3(GetWorld()); it3; ++it3)
	{
		knife3 = *it3;
	}
	FVector Location4 = GetActorLocation() + (10, 0, 0);
	FRotator Rotation4 = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(Knife, Location, Rotation);
	for (TActorIterator<AKnife>it4(GetWorld()); it4; ++it4)
	{
		knife4 = *it4;
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
	direction.Normalize();
	AddMovementInput(direction, value);
	
}

void AJett::Vertical(float value)
{
	
	direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	direction.Normalize();
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
	direction.Normalize();
	LaunchCharacter(direction * jumpdashDistance, true, true);
	
}

void AJett::Dash()
{
	direction = GetActorForwardVector();
	direction.Normalize();
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
		knife0->KnifeDirectionReset();
		knife1->KnifeDirectionReset();
		knife2->KnifeDirectionReset();
		knife3->KnifeDirectionReset();
		knife4->KnifeDirectionReset();
		knife0->SetActorLocation(GetActorLocation() + (100, 100, 100));
		knife1->SetActorLocation(GetActorLocation());
		knife2->SetActorLocation(GetActorLocation());
		knife3->SetActorLocation(GetActorLocation());
		knife4->SetActorLocation(GetActorLocation());
		MaxKnife = 5;
	}
	else
	{
		if (MaxKnife == 5)
		{
			knife0->SetActorTickEnabled(false);
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
		else
		{
			knife4->KnifeThrowing();
			MaxKnife -= 1;
		}

	}

}