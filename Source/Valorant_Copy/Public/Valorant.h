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

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
		TSubclassOf<class UCharacterSelectWidget> SelectWidgetBP;

	void MinusAmmo(int32 count);

	void ReloadAmmo();

	UFUNCTION(BlueprintImplementableEvent)
	void Select1();

	class UPlayerUI* player_UI;
	class AJett* player;
	class UCharacterSelectWidget* SelectWidget;


private:
	int32 ammo = 25;

};
