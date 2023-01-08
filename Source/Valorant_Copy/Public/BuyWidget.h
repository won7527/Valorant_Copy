// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuyWidget.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_COPY_API UBuyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Rifle;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Shotgun;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Sniper;

private:

	UFUNCTION()
		void Rifle();

	UFUNCTION()
		void Shotgun();

	UFUNCTION()
		void Sniper();
};
