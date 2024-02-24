// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "msHUD.generated.h"

class UmsOverlayWidget;
/**
 *
 */
UCLASS()
class MIDNIGHTSUNZ_API AmsHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitOverlayWidget();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UmsOverlayWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UmsOverlayWidget> OverlayWidget;
};
