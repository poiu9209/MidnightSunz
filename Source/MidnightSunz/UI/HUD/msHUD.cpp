// Fill out your copyright notice in the Description page of Project Settings.


#include "msHUD.h"
#include "Blueprint/UserWidget.h"
#include "MidnightSunz/UI/Widgets/msOverlayWidget.h"

void AmsHUD::InitOverlayWidget()
{
	check(OverlayWidgetClass);

	OverlayWidget = CreateWidget<UmsOverlayWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();
}
