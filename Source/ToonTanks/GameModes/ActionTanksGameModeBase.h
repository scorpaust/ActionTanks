// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ActionTanksGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;
/**
 * 
 */
UCLASS()
class TOONTANKS_API AActionTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AActionTanksGameModeBase();

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay;

private:

	APawnTank* PlayerTank;

	APlayerControllerBase* PlayerControllerRef;

	int32 TargetTurrets;

	void HandleGameStart();

	void HandleGameOver(bool PlayerWon);

	int32 GetTargetTurretCount();

};
