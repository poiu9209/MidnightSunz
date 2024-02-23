// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "msCharacterBase.generated.h"

UCLASS()
class MIDNIGHTSUNZ_API AmsCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AmsCharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
