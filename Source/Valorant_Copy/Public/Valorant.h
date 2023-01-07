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

	//����
	void ShotgunMinusAmmo();

	void ShotgunReloadAmmo();

	//����
	void SniperMinusAmmo();

	void SniperReloadAmmo();

	void ChangeWeapon();

	void SniperAimMod();

	UFUNCTION(BlueprintImplementableEvent)
	void Select1();

	//�÷��̾� ui����
	class UPlayerUI* player_UI;
	class AJett* player;
	//����â ���� ����
	class UCharacterSelectWidget* SelectWidget;
	//���� ���� ���� ����
	class USniperAimWidget* sniperWidget;

	UPROPERTY(EditAnywhere)
	bool isScope = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HP)
	int32 playerHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameScore)
		int32 winScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameScore)
		int32 loseScore = 0;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameScore)
		TArray<AValEnemy> enemys;*/

	UFUNCTION()
	void Damaged(int32 deal);

	FTimerHandle TimerHandle_ResetMap;

	UFUNCTION()
	void RestartMap();



	

private:
	int32 ammo = 25;

	int32 shotgunAmmo = 8;
	int32 sniperAmmo = 5;

	class AValEnemy* target;


};
