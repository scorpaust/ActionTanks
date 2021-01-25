// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"


class APawnTank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
public:

	APawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	APawnTank* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange;

	FTimerHandle FireRateTimerHandle;

	void CheckFireCondition();

	float ReturnDistanceToPlayer();
	
};
