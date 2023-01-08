// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSelectWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Valorant.h"
#include "Jett.h"

void UCharacterSelectWidget::NativeConstruct()
{
	btn_Select1->OnClicked.AddDynamic(this, &UCharacterSelectWidget::Select1);
	btn_Select2->OnClicked.AddDynamic(this, &UCharacterSelectWidget::Select2);
}

void UCharacterSelectWidget::Select1()
{
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AValorant* myGM = Cast<AValorant>(gm);
	if (myGM != nullptr){ 
		myGM->isOnSreenF();
		myGM->Select1();
		//UGameplayStatics::OpenLevel(GetWorld(), TEXT("Valorant"));
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
		this->RemoveFromParent();
	}
}

void UCharacterSelectWidget::Select2()
{
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AValorant* myGM = Cast<AValorant>(gm);
	if (myGM != nullptr) {
		myGM->isOnSreenF();
	}
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
	this->RemoveFromParent();
}
