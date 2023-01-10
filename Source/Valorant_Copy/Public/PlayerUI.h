// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_COPY_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* UIammo; 

	UPROPERTY(EditAnywhere, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* UIplayerHP;

	UPROPERTY(EditAnywhere, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* UIwinRound;

	UPROPERTY(EditAnywhere, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* UIloseRound;

	UPROPERTY(EditAnywhere, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* UImoney;

	UPROPERTY(EditAnywhere, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* UIenemyNum;

	UPROPERTY(EditAnywhere, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* UItimer;

	//void PrintAmmo();



};
