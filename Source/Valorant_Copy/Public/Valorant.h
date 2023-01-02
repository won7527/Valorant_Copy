// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Valorant.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_COPY_API AValorant : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetAmmo() { return ammo;}

	UPROPERTY(EditAnywhere, Category=MyDefaultSetting)
	TSubclassOf<class UPlayerUI> playerWidget;

	void MinusAmmo(int32 count);

private:
	int32 ammo = 25;

};
