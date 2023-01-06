// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmokeGrenade.generated.h"

UCLASS()
class VALORANT_COPY_API ASmokeGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmokeGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void KeepPressed();
	void ReleasedC();
	void DestroySmoke();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
	float moveSpeed = 1000.0f;
	bool keepPressed;
	float angle;
	float initS = 10;
	float time = 0;
	FVector direction;
	FVector velocity;
	FVector position;

	bool isOverlap = false;

	UPROPERTY(EditAnywhere)
	class USphereComponent* sphComp;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComp;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:


};
