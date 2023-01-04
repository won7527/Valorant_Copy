// Fill out your copyright notice in the Description page of Project Settings.


#include "Valorant.h"
#include "PlayerUI.h"
#include "CharacterSelectWidget.h"
#include "SniperAimWidget.h"
#include "Jett.h"
#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void AValorant::BeginPlay()
{
	Super::BeginPlay();

	
	player_UI = CreateWidget<UPlayerUI>(GetWorld(), playerWidget);
	SelectWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), SelectWidgetBP);
	sniperWidget = CreateWidget<USniperAimWidget>(GetWorld(), SniperAimWidgetBP);
	AActor* playerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AJett::StaticClass());

	player = Cast<AJett>(playerActor);

	if (SelectWidget != nullptr) {
		SelectWidget->AddToViewport();
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}


	if (player_UI != nullptr) {
		player_UI->UIammo->SetText(FText::AsNumber(ammo));
		player_UI->AddToViewport();
		//player_UI->PrintAmmo();
	}

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
		player_UI->UIammo->SetText(FText::AsNumber(ammo));
	}

	if (player->isWeapon2Use == true) {
		player_UI->UIammo->SetText(FText::AsNumber(shotgunAmmo));
	}

	if (player->isWeapon3Use == true) {
		player_UI->UIammo->SetText(FText::AsNumber(sniperAmmo));
	}
}

void AValorant::SniperAim()
{
	if (sniperWidget != nullptr) {
		sniperWidget->AddToViewport();
	}
}

