
// Fill out your copyright notice in the Description page of Project Settings.


#include "msPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "MidnightSunz/Input/msEnhancedInputComponent.h"
#include "MidnightSunz/AbilitySystem/msAbilitySystemComponent.h"
#include "MidnightSunz/Interface/msCombatInterface.h"

void AmsPlayerController::ShowDamageNumber_Implementation(ACharacter* TargetCharacter, float DamageAmount)
{
	if (!IsValid(TargetCharacter) && !IsLocalController())
	{
		return;
	}

	if (ImsCombatInterface* CombatInterface = Cast<ImsCombatInterface>(TargetCharacter))
	{
		CombatInterface->Execute_ShowDamageText(TargetCharacter, DamageAmount);
	}
}

void AmsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(DefaultMappingContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}

void AmsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UmsEnhancedInputComponent* EnhancedInputComponent = CastChecked<UmsEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AmsPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AmsPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
}

void AmsPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (auto ASC = GetAbilitySystemComponent())
	{
		ASC->AbilityInputTagReleased(InputTag);
	}
}

void AmsPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (auto ASC = GetAbilitySystemComponent())
	{
		ASC->AbilityInputTagHeld(InputTag);
	}
}

UmsAbilitySystemComponent* AmsPlayerController::GetAbilitySystemComponent()
{
	if (!AbilitySystemComponent)
	{
		AbilitySystemComponent = Cast<UmsAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AbilitySystemComponent;
}
