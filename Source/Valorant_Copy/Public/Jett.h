// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Jett.generated.h"

UCLASS()
class VALORANT_COPY_API AJett : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJett();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UStaticMeshComponent* meshComp;

	void Turn(float value);

	void LookUp(float value);

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float walkSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float runSpeed = 800.0f;

	FVector direction;

	UFUNCTION()
	void Horizontal(float value);
	UFUNCTION()
	void Vertical(float value);
	
	void InputJump ();

	void Walking();

	void WalkEnd();
};
