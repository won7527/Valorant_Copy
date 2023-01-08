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
	AValorant();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetAmmo() { return ammo;}

	UPROPERTY(EditAnywhere, Category=MyDefaultSetting)
	TSubclassOf<class UPlayerUI> playerWidget;

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UCharacterSelectWidget> SelectWidgetBP;

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class USniperAimWidget> SniperAimWidgetBP;

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class URoundLoseWidget> RLoseWidgetBP;

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class URoundWinWidget> RWinWidgetBP;

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UVictoryWidget> VictoryWidgetBP;

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UDefeatWidget> DefeatWidgetBP;

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UBuyWidget> BuyWidgetBP;



	void MinusAmmo(int32 count);

	void ReloadAmmo();

	//샷건
	void ShotgunMinusAmmo();

	void ShotgunReloadAmmo();

	//스나
	void SniperMinusAmmo();

	void SniperReloadAmmo();

	void ChangeWeapon();

	void SniperAimMod();

	UFUNCTION(BlueprintImplementableEvent)
	void Select1();

	//플레이어 ui변수
	class UPlayerUI* player_UI;
	class AJett* player;
	//선택창 위젯 변수
	class UCharacterSelectWidget* SelectWidget;
	//스나 조준 위젯 변수
	UPROPERTY(EditAnywhere)
	class USniperAimWidget* sniperWidget;
	
	class URoundLoseWidget* RLoseWidget;

	class URoundWinWidget* RWinWidget;

	class UBuyWidget* BuyWidget;

	UPROPERTY(EditAnywhere)
	bool isScope = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyDefaultSetting)
	int32 playerHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyDefaultSetting)
		int32 winScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyDefaultSetting)
		int32 loseScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyDefaultSetting)
	int32 enemyNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyDefaultSetting)
	int32 Money = 0;

	UFUNCTION()
	void Damaged(int32 deal);

	FTimerHandle TimerHandle_ResetMap;

	UFUNCTION()
	void LoseRound();

	UFUNCTION()
	void WinRound();

	UFUNCTION()
	void RWinWidgetPrint();

	UFUNCTION()
	void SpendMoney(int32 price);

	UFUNCTION()
	void isOnSreenT();

	UFUNCTION()
	void isOnSreenF();

	UFUNCTION()
	void PrintBuy();

	UFUNCTION()
	void RemoveBuy();


	

private:

	//RoundScoreTxt file
	FString winFilePath = FString("../../../Content/MyBP/SaveRound/WinRound.txt");
	FString loseFilePath = FString("../../../Content/MyBP/SaveRound/LoseRound.txt");
	FString moneyFilePath = FString("../../../Content/MyBP/SaveRound/money.txt");

	int32 ammo = 25;

	int32 shotgunAmmo = 8;
	int32 sniperAmmo = 5;

	class AValEnemy* target;

public:

	virtual void Tick(float DeltaTime) override;

};
