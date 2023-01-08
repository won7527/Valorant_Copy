// Fill out your copyright notice in the Description page of Project Settings.


#include "Valorant.h"
#include "PlayerUI.h"
#include "CharacterSelectWidget.h"
#include "SniperAimWidget.h"
#include "Jett.h"
#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "ValEnemy.h"
#include "EngineUtils.h"
#include "GameFramework/GameMode.h"
#include "RoundLoseWidget.h"
#include "RoundWinWidget.h"
#include "VictoryWidget.h"
#include "DefeatWidget.h"
#include "BuyWidget.h"

AValorant::AValorant()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AValorant::BeginPlay()
{
	Super::BeginPlay();

	
	player_UI = CreateWidget<UPlayerUI>(GetWorld(), playerWidget);
	SelectWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), SelectWidgetBP);
	sniperWidget = CreateWidget<USniperAimWidget>(GetWorld(), SniperAimWidgetBP);
	RLoseWidget = CreateWidget<URoundLoseWidget>(GetWorld(), RLoseWidgetBP);
	RWinWidget = CreateWidget<URoundWinWidget>(GetWorld(), RWinWidgetBP);

	BuyWidget = CreateWidget<UBuyWidget>(GetWorld(), BuyWidgetBP);

	//player cast
	AActor* playerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AJett::StaticClass());
	player = Cast<AJett>(playerActor);

	FString winText;
	FFileHelper::LoadFileToString(winText ,*winFilePath);
	winScore = FCString::Atoi(*winText);

	FString loseText;
	FFileHelper::LoadFileToString(loseText, *loseFilePath);
	loseScore = FCString::Atoi(*loseText);

	FString moneyText;
	FFileHelper::LoadFileToString(moneyText, *moneyFilePath);
	Money = FCString::Atoi(*moneyText);

	if (SelectWidget != nullptr) {
		SelectWidget->AddToViewport();
		isOnSreenT();
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}

	//ammo = jet->GetAmmo();

	if (player_UI != nullptr) {
		player_UI->UIammo->SetText(FText::AsNumber(ammo));
		player_UI->UIplayerHP->SetText(FText::AsNumber(playerHP));

		player_UI->UIwinRound->SetText(FText::AsNumber(winScore));
		player_UI->UIloseRound->SetText(FText::AsNumber(loseScore));
		player_UI->UImoney->SetText(FText::AsNumber(Money));

		player_UI->AddToViewport();
		//player_UI->PrintAmmo();
	}

	for (TActorIterator<AValEnemy> it(GetWorld()); it; ++it) {
		target = *it;

		if (target != nullptr) {

			enemyNum++;
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), enemyNum));

		}
	}

}

void AValorant::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

}

void AValorant::MinusAmmo(int32 count)
{
	ammo -= count;  
	player_UI->UIammo->SetText(FText::AsNumber(ammo));
}

void AValorant::ReloadAmmo()
{
	ammo = 25;
	player_UI->UIammo->SetText(FText::AsNumber(ammo));
}

void AValorant::ShotgunMinusAmmo()
{
	shotgunAmmo--;
	player_UI->UIammo->SetText(FText::AsNumber(shotgunAmmo));
}

void AValorant::ShotgunReloadAmmo()
{
	shotgunAmmo++;
	player_UI->UIammo->SetText(FText::AsNumber(shotgunAmmo));
}

void AValorant::SniperMinusAmmo()
{
	sniperAmmo--;
	player_UI->UIammo->SetText(FText::AsNumber(sniperAmmo));
}

void AValorant::SniperReloadAmmo()
{
	sniperAmmo = 5;
	player_UI->UIammo->SetText(FText::AsNumber(sniperAmmo));
}

void AValorant::ChangeWeapon()
{
	if (player->isWeapon1Use == true) {
		if(player_UI != nullptr)
		{ 
		player_UI->UIammo->SetText(FText::AsNumber(ammo));
		}	
	}

	if (player->isWeapon2Use == true) {
		player_UI->UIammo->SetText(FText::AsNumber(shotgunAmmo));
	}

	if (player->isWeapon3Use == true) {
		player_UI->UIammo->SetText(FText::AsNumber(sniperAmmo));
	}
}

void AValorant::SniperAimMod()
{
	if (sniperWidget != nullptr) {
		if (isScope == false) {
			sniperWidget->AddToViewport();
			isScope = true;
		}
		else {
			sniperWidget->RemoveFromParent();
			isScope = false;
		}
	}
}

void AValorant::Damaged(int32 deal)
{
	playerHP -= deal;
	player_UI->UIplayerHP->SetText(FText::AsNumber(playerHP));
	//when player die
	if (playerHP <= 0) {
		if (RLoseWidget != nullptr) {
			RLoseWidget->AddToViewport();
		}
		if (player != nullptr) {
			player->Destroy();
			player_UI->RemoveFromParent();
			GetWorldTimerManager().SetTimer(TimerHandle_ResetMap, this, &AValorant::LoseRound, 2.5f, false);
			}
	}
}

void AValorant::LoseRound()
{
	loseScore++;
	if (loseScore >= 3) {
		UDefeatWidget* DefeatWidget = CreateWidget<UDefeatWidget>(GetWorld(), DefeatWidgetBP);
		if (DefeatWidget != nullptr) {
			DefeatWidget->AddToViewport();
			FFileHelper::SaveStringToFile(FString::FromInt(0), *loseFilePath);
			FFileHelper::SaveStringToFile(FString::FromInt(0), *winFilePath);
			FFileHelper::SaveStringToFile(FString::FromInt(0), *moneyFilePath);
		}
		if (player_UI != nullptr) {
			player_UI->RemoveFromParent();
		}
		if (RLoseWidget != nullptr) {
			RLoseWidget->RemoveFromParent();
		}
	}
	else {
		FFileHelper::SaveStringToFile(FString::FromInt(loseScore), *loseFilePath);
		FFileHelper::SaveStringToFile(FString::FromInt(Money), *moneyFilePath);
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Valorant"));
	}
}

void AValorant::WinRound()
{
	winScore++;
	if (winScore >= 3) {
		UVictoryWidget* VictoryWidget = CreateWidget<UVictoryWidget>(GetWorld(), VictoryWidgetBP);
		if (VictoryWidget != nullptr) {
			VictoryWidget->AddToViewport();
			FFileHelper::SaveStringToFile(FString::FromInt(0), *winFilePath);
			FFileHelper::SaveStringToFile(FString::FromInt(0), *loseFilePath);
			FFileHelper::SaveStringToFile(FString::FromInt(0), *moneyFilePath);
		}
		if (player_UI != nullptr) {
			player_UI->RemoveFromParent();
		}
		if (RWinWidget != nullptr) {
			RWinWidget->RemoveFromParent();
		}
	}
	else {
		FFileHelper::SaveStringToFile(FString::FromInt(winScore), *winFilePath);
		FFileHelper::SaveStringToFile(FString::FromInt(Money), *moneyFilePath);
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Valorant"));
	}
}

void AValorant::RWinWidgetPrint()
{
	if (RWinWidget != nullptr) {
		RWinWidget->AddToViewport();
	}
}

void AValorant::SpendMoney(int32 price)
{
	Money -= price;
	if (player_UI != nullptr) {
		player_UI->UImoney->SetText(FText::AsNumber(Money));
	}
}

void AValorant::isOnSreenT()
{
	if (player != nullptr) {
		player->isOnSreen = true;
	}
}

void AValorant::isOnSreenF()
{
	if (player != nullptr) {
		player->isOnSreen = false;
	}
}

void AValorant::PrintBuy()
{
	if (BuyWidget != nullptr) {
		BuyWidget->AddToViewport();
	}
	isOnSreenT();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void AValorant::RemoveBuy()
{
	if (BuyWidget != nullptr) {
		BuyWidget->RemoveFromParent();
	}
	isOnSreenF();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
}




