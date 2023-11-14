// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

#include "CustomCharacterMovementComponent.h"
#include "MainCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	if(Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
}

void UMainAnimInstance::UpdateAnimationProperties()
{
	if(Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
	
	if(Pawn)
	{
		AMainCharacter* Character = Cast<AMainCharacter>(Pawn);
		const FVector Speed = Pawn->GetVelocity();
		const FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);

		MovementSpeed = LateralSpeed.Length();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();

		const auto InvTransform = Pawn->GetActorTransform().InverseTransformVector(Speed);
		HorizontalVelocity =  InvTransform.Y;
		VerticalVelocity = InvTransform.Z;
		bIsClimbing = Character->GetCustomMovementComponent()->IsClimbing();
	}
}
