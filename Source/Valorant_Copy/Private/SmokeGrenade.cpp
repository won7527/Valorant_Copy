// Fill out your copyright notice in the Description page of Project Settings.


#include "SmokeGrenade.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ASmokeGrenade::ASmokeGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(15);
		RootComponent  = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	}
	
}

// Called when the game starts or when spawned
void ASmokeGrenade::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ASmokeGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (keepPressed)
	{
		APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		//FVector camLocation = camManager->GetCameraLocation();
		FVector camForward = camManager->GetCameraRotation().Vector();

		direction = camForward;
		SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
	}
	
}

void ASmokeGrenade::KeepPressed()
{
	keepPressed = true;
}

void ASmokeGrenade::ReleasedC()
{
	keepPressed = false;
	
}
void ASmokeGrenade::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}