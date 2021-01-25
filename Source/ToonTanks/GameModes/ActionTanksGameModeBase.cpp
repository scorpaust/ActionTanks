// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionTanksGameModeBase.h"
#include "../Pawns/PawnTurret.h"
#include "../Pawns/PawnTank.h"
#include "../PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"


AActionTanksGameModeBase::AActionTanksGameModeBase() {

	TargetTurrets = 0.f;

	StartDelay = 6.f;

	PlayerControllerRef = nullptr;

}

void AActionTanksGameModeBase::BeginPlay() {

	Super::BeginPlay();

	HandleGameStart();

}

void AActionTanksGameModeBase::ActorDied(AActor* DeadActor) {

	if (DeadActor == PlayerTank) {

		PlayerTank->HandleDestruction();

		HandleGameOver(false);

		if (PlayerControllerRef) {

			PlayerControllerRef->SetPlayerEnabledState(false);

		}

	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) {

		DestroyedTurret->HandleDestruction();

		if (--TargetTurrets == 0) {

			HandleGameOver(true);
		}

	}

}

void AActionTanksGameModeBase::HandleGameStart()
{

	TargetTurrets = GetTargetTurretCount();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	if (PlayerControllerRef) {

		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnabledHandle;

		FTimerDelegate PlayerEnabledDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnabledHandle, PlayerEnabledDelegate, StartDelay, false);

	}

}

void AActionTanksGameModeBase::HandleGameOver(bool PlayerWon)
{

	GameOver(PlayerWon);

}

int32 AActionTanksGameModeBase::GetTargetTurretCount() {

	TArray<AActor*> TurretActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);

	return TurretActors.Num();

}
