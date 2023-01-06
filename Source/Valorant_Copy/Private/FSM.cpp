// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM.h"
#include "Jett.h"
#include "ValEnemy.h"
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UFSM::UFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFSM::BeginPlay()
{
	Super::BeginPlay();

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), AJett::StaticClass());

	target = Cast<AJett>(actor);

	me = Cast<AValEnemy>(GetOwner());
	
}


// Called every frame
void UFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	

	destination = target->GetActorLocation();
	dir = destination - me->GetActorLocation();

	switch (mState)
	{
		case EEnemyState::Idle:
		IdleState();
		break;
		case EEnemyState::Move:
		MoveState();
		break;
		case EEnemyState::Attack:
		AttackState();
		break;
		case EEnemyState::Damage:
		DamageState();
		case EEnemyState::Die:
		DieState();

	}
}

void UFSM::IdleState()
{
	/*currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > idleDelayTime)
	{
		mState = EEnemyState::Move;
		
		currentTime = 0;
	}*/
	mState = EEnemyState::Move;

}

void UFSM::MoveState()
{
	me->ismove = true;
	//destination = target->GetActorLocation();
	//dir = destination - me->GetActorLocation();
	if (dir.Size() < followRange)
	{
		me->AddMovementInput(dir.GetSafeNormal());
	}

	if (dir.Size() <= attackRange)
	{
		mState = EEnemyState::Attack;
	}

}

void UFSM::AttackState()
{
	me->ismove = false;
	me->SetActorRotation((target->GetActorLocation() - me->GetActorLocation()).Rotation());
	if (dir.Size() > attackRange)
	{
		mState = EEnemyState::Move;
	}
	me->FireDelay();

}

void UFSM::DamageState()
{
}

void UFSM::DieState(){}

