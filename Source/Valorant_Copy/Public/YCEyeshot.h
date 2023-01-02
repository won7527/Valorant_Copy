// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YCEyeshot.generated.h"

UCLASS()
class VALORANT_COPY_API AYCEyeshot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYCEyeshot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// You can expose some of your collision query data as properties to help customize and debug 
	// Here we expose the collision channel we want to run the query on, and set it to only hit Pawns.


};
