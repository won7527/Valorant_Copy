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

	//void PrintAmmo();


};
