// Fill out your copyright notice in the Description page of Project Settings.


#include "msWidgetController.h"

void UmsWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UmsWidgetController::BroadcastInitialValues()
{
}

void UmsWidgetController::BindCallbacksToDependencies()
{
}
