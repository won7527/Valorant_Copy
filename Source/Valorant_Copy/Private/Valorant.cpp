// Fill out your copyright notice in the Description page of Project Settings.


#include "Valorant.h"
#include "PlayerUI.h"
#include "Jett.h"
#include "MainWidget.h"

void AValorant::BeginPlay()
{
	UPlayerUI* player_UI = CreateWidget<UPlayerUI>(GetWorld(), playerWidget);

	if (player_UI != nullptr) {
		player_UI->AddToViewport();
		player_UI->PrintAmmo();
	}
}

void AValorant::MinusAmmo(int32 count)
{

	ammo -= count;  

}
