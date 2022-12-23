// Fill out your copyright notice in the Description page of Project Settings.


#include "Jett.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AJett::AJett()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collison"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));

}

// Called when the game starts or when spawned
void AJett::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJett::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	direction = FTransform(GetControlRotation()).TransformVector(direction);
	
	FVector P0 = GetActorLocation();
	FVector P = P0 + direction * walkSpeed * DeltaTime;
	SetActorLocation(P);
	//AddMovementInput(direction);
	direction = FVector::ZeroVector;
	

}

// Called to bind functionality to input
void AJett::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJett::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AJett::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &AJett::InputHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &AJett::InputVertical);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AJett::InputJump);

}

void AJett::Turn(float value)
{
	AddControllerYawInput(value);
}

void AJett::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void AJett::InputHorizontal(float value)
{
	direction.Y = value;
}

void AJett::InputVertical(float value)
{
	direction.X = value;
}

void AJett::InputJump()
{
	Jump();
}