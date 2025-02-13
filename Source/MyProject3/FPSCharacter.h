// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "FPSCharacter.generated.h"


UCLASS()
class MYPROJECT3_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))

	class UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input");
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input");
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input");
	class UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input");
	class UInputAction* IA_Jump;

	//UPROPERTY(EditAnywhere, Category = "Enhanced Input");
	//class UInputAction* IA_Interact;

	void MoveInput(const FInputActionValue& InputValue);
	void LookInput(const FInputActionValue& InputValue);
	void JumpInput();
	//UFUNCTION(BlueprintImplementableEvent)
	//void Interact();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
