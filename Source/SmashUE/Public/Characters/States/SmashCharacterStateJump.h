// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmashCharacterState.h"
#include "SmashCharacterStateJump.generated.h"


class UCharacterMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateJump : public USmashCharacterState
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AnimMontageJump;

	UPROPERTY(EditAnywhere)
	float JumpWalkSpeed;

	UPROPERTY(EditAnywhere)
	float JumpMaxHeight;

	UPROPERTY(EditAnywhere)
	float JumpDuration;

	UPROPERTY(EditAnywhere)
	float JumpAirControl;

private:
	float time;
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
};
