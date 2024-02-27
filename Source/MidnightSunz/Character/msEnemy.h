// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "msCharacterBase.h"
#include "msEnemy.generated.h"

/**
 *
 */
UCLASS()
class MIDNIGHTSUNZ_API AmsEnemy : public AmsCharacterBase
{
	GENERATED_BODY()

public:
	AmsEnemy();

	// begin ImsCombatInterface
	virtual void Die() override;
	// end ImsCombatInterface

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

};
