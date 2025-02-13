// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"


#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>
// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, "Why are we doing FPS");
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//EnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Input->BindAction("Move", IE_Pressed, this, &AFPSCharacter::Jump);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping,0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(IA_Move, ETriggerEvent::Triggered,this,&AFPSCharacter::MoveInput);
		Input->BindAction(IA_Jump, ETriggerEvent::Triggered,this,&AFPSCharacter::JumpInput);
		Input->BindAction(IA_Look, ETriggerEvent::Triggered,this,&AFPSCharacter::LookInput);
//		Input->BindAction(IA_Interact,ETriggerEvent::Triggered, this, &AFPSCharacter::Interact);
	}

	

}

void AFPSCharacter::MoveInput(const FInputActionValue& InputValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Pressed Input Action IA_Move"));

	FVector2D InputVector = InputValue.Get<FVector2d>();
	if (IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Add Movement Input
		//Depending on WASD pressed, it will move forwards and rightwards
		AddMovementInput(ForwardDirection,InputVector.Y);
		AddMovementInput(RightDirection,InputVector.X);
	}
}

void AFPSCharacter::LookInput(const FInputActionValue& InputValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Pressed Input Action IA_Look"));

	FVector2d InputVector = InputValue.Get<FVector2d>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(-InputVector.Y);
		AddControllerPitchInput(InputVector.X);
	}
}

void AFPSCharacter::JumpInput()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Pressed Input Action IA_Jump"));

	AFPSCharacter::Jump();
}

//void AFPSCharacter::Interact()
//{
//	AFPSCharacter::Interact();
//}

