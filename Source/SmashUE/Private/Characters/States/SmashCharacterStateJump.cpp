// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateJump.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"

// Called when the game starts
void USmashCharacterStateJump::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

ESmashCharacterStateID USmashCharacterStateJump::GetStateID()
{
	return ESmashCharacterStateID::Jump;
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	GEngine->AddOnScreenDebugMessage(
	-1,
	3.f,
	FColor::Cyan,
	TEXT("Enter StateJump")
	);
	CharacterMovementComponent = Character->GetCharacterMovement();
	CharacterMovementComponent->AirControl = JumpAirControl;
	CharacterMovementComponent->JumpZVelocity = JumpMaxHeight;
	Character->PlayAnimMontage(AnimMontageJump);
	Character->Jump();
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);

	GEngine->AddOnScreenDebugMessage(
	-1,
	3.f,
	FColor::Red,
	TEXT("Exit StateJump")
	);
}

void USmashCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	time += DeltaTime;
	if(FMath::Abs(Character->GetInputMoveX()) > Settings->InputMoveXThreshold)
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector,  Character->GetOrientX() * DeltaTime);
	}

	if(CharacterMovementComponent->Velocity.Z < 0.f)
	{
		time = 0.f; 
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}

	
}

