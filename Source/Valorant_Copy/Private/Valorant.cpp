// Fill out your copyright notice in the Description page of Project Settings.


#include "Valorant.h"
#include "PlayerUI.h"
#include "CharacterSelectWidget.h"
#include "Jett.h"
#include "MainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void AValorant::BeginPlay()
{
	Super::BeginPlay();

	
	player_UI = CreateWidget<UPlayerUI>(GetWorld(), playerWidget);
	SelectWidget = CreateWidget<UCharacterSelectWidget>(GetWorld(), SelectWidgetBP);
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



