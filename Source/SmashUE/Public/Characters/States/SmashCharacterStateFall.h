// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SmashCharacterState.h"
#include "SmashCharacterStateFall.generated.h"

class UCharacterMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateFall : public USmashCharacterState
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float FallHorizontalMoveSpeed = 400.f;

	UPROPERTY(EditAnywhere)
	float AirControl = 1.f;

	UPROPERTY(EditAnywhere)
	float FallGravityScale = 3.f;

	UPROPERTY(EditAnywhere)
	float FallFastGravityScale = 10.f;

public:
	// Called every frame
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AnimMontageFall;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AnimMontageLand;
	
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;

private:
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
	bool Playing;
};
