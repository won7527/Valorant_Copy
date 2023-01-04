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

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class USniperAimWidget> SniperAimWidgetBP;



	void MinusAmmo(int32 count);

	void ReloadAmmo();

	//샷건
	void ShotgunMinusAmmo();

	void ShotgunReloadAmmo();

	//스나
	void SniperMinusAmmo();

	void SniperReloadAmmo();

	void ChangeWeapon();

	void SniperAim();

	UFUNCTION(BlueprintImplementableEvent)
	void Select1();

	//플레이어 ui변수
	class UPlayerUI* player_UI;
	class AJett* player;
	//선택창 위젯 변수
	class UCharacterSelectWidget* SelectWidget;
	//스나 조준 위젯 변수
	class USniperAimWidget* sniperWidget;


private:
	int32 ammo = 25;

	int32 shotgunAmmo = 8;
	int32 sniperAmmo = 5;

	bool isScope = false;
};
