// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank() {

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Camera->SetupAttachment(SpringArm);

	MoveSpeed = 100.f;

	RotateSpeed = 80.f;
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

}

void APawnTank::CalculateMoveInput(float Value)
{

	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f);

}

void APawnTank::CalculateRotateInput(float Value)
{

	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;

	FRotator Rotation = FRotator(0.f, RotateAmount, 0.f);

	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{

	AddActorLocalOffset(MoveDirection, true);

}

void APawnTank::Rotate()
{

	AddActorLocalRotation(RotationDirection, true);

}

void APawnTank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {

	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);

	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
}



// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();

	Move();

}

