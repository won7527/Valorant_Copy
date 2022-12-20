// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class VALORANT_COPY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//박스 충돌체 컴포넌트
	UPROPERTY(EditAnywhere)
		class UBoxComponent* BoxComp;
	//스테틱 메시 컴포넌트
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshComp;

	//속력변수
	UPROPERTY(EditAnywhere)
		float moveSpeed = 500;

private:
	float h;
	float v;

	void moveHorizontal(float value);
	void moveVertical(float value);

};
