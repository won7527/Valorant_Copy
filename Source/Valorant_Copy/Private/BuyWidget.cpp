// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Jett.h"
#include "Valorant.h"

void UBuyWidget::NativeConstruct()
{
	btn_Rifle->OnClicked.AddDynamic(this, &UBuyWidget::Rifle);
	btn_Shotgun->OnClicked.AddDynamic(this, &UBuyWidget::Shotgun);
	btn_Sniper->OnClicked.AddDynamic(this, &UBuyWidget::Sniper);
}

void UBuyWidget::Rifle()
{
	AActor* playerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AJett::StaticClass());
	AJett* player = Cast<AJett>(playerActor);
	if (player != nullptr) {

	}
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AValorant* myGM = Cast<AValorant>(gm);
	if (myGM != nullptr) {
		myGM->SpendMoney(100);
	}
}

void UBuyWidget::Shotgun()
{
	AActor* playerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AJett::StaticClass());
	AJett* player = Cast<AJett>(playerActor);
	if (player != nullptr) {

	}
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AValorant* myGM = Cast<AValorant>(gm);
	if (myGM != nullptr) {
		myGM->SpendMoney(200);
	}
}

void UBuyWidget::Sniper()
{
	AActor* playerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AJett::StaticClass());
	AJett* player = Cast<AJett>(playerActor);
	if (player != nullptr) {

	}
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AValorant* myGM = Cast<AValorant>(gm);
	if (myGM != nullptr) {
		myGM->SpendMoney(400);
	}
}
