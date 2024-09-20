// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/States/SmashCharacterStateFall.h"

#include "Characters/SmashCharacter.h"
#include "Characters/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"


// Called when the game starts
void USmashCharacterStateFall::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

ESmashCharacterStateID USmashCharacterStateFall::GetStateID()
{
	return ESmashCharacterStateID::Fall;
}

void USmashCharacterStateFall::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
			GEngine->AddOnScreenDebugMessage(
	-1,
	3.f,
	FColor::Cyan,
	TEXT("Enter StateFall")
	);
	CharacterMovementComponent = Character->GetCharacterMovement();
	Character->PlayAnimMontage(AnimMontageFall);
	CharacterMovementComponent->GravityScale = FallGravityScale;
	CharacterMovementComponent->AirControl = AirControl;
}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Playing = !Playing;
	CharacterMovementComponent->GravityScale = 1.f;
		GEngine->AddOnScreenDebugMessage(
	-1,
	3.f,
	FColor::Red,
	TEXT("Exit StateFall")
	);
}

void USmashCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if(FMath::Abs(Character->GetInputMoveX()) > Settings->InputMoveXThreshold)
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector,  Character->GetOrientX() * DeltaTime);
	}
	if(AnimMontageFall)
	{
		if(CharacterMovementComponent->IsMovingOnGround())
		{
			if(AnimMontageLand && !Playing)
			{
				Character->PlayAnimMontage(AnimMontageLand);
				Playing = !Playing;
			}
			if(AnimMontageLand && Playing)
			{
				if (!Character->GetMesh()->GetAnimInstance()->Montage_IsPlaying(AnimMontageLand))
				{
					StateMachine->ChangeState(ESmashCharacterStateID::Idle);
				}
			}
		}
	}
	else if(AnimMontageFall == nullptr) StateMachine->ChangeState(ESmashCharacterStateID::Idle);

}

