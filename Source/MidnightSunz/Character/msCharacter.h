// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "msCharacterBase.h"
#include "msCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 *
 */
UCLASS()
class MIDNIGHTSUNZ_API AmsCharacter : public AmsCharacterBase
{
	GENERATED_BODY()

public:
	AmsCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void InitAbilityActorInfo() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
};
