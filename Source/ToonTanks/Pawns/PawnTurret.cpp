// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"



APawnTurret::APawnTurret() {

	FireRate = 2.f;

	FireRange = 580.f;
}

void APawnTurret::BeginPlay() {

	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void APawnTurret::HandleDestruction()
{

	Super::HandleDestruction();

	Destroy();

}

void APawnTurret::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) {

		return;
	
	}
	else {

		RotateTurret(PlayerPawn->GetActorLocation());

	}

}

void APawnTurret::CheckFireCondition() {

	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) return;

	if (ReturnDistanceToPlayer() <= FireRange) {

		Fire();

	}

}

float APawnTurret::ReturnDistanceToPlayer() {

	if (!PlayerPawn) return 0.f;

	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation());

}