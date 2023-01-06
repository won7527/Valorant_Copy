// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class VALORANT_COPY_API UCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Select1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		class UButton* btn_Select2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AJett> jet;

	virtual void NativeConstruct() override;

private:

	//UFUNTION을 넣지 않으면 실행 안됨
	UFUNCTION()
	void Select1();
	UFUNCTION()
	void Select2();
};
