// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerInputComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	_CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

	_SpringArmComponent->SetupAttachment(_CameraComponent);
	_CameraComponent->SetupAttachment(RootComponent);

	_CameraComponent->bUsePawnControlRotation = true;
	*/
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/* INPUT / CONTROLS*/

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/* Adding input mapping context // Checking if Player Controller is valid */
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		/* Getting local player subsystem // Checking if Enhanced Player Subsystem is valid */
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//If valid add input context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	/* Checked the input component and called the input test action // If triggered it calls function test input*/
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);

		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		Input->BindAction(PrimaryInput, ETriggerEvent::Triggered, this, &APlayerCharacter::PrimaryAction);

		Input->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Sprint);

		Input->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Crouch);
	}
}


void APlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		//Get forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		//If pressing W want to move in this direction:
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		//If pressing D want to move in this direction:
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Add movement input
		/*
			Gets forward facing direction and then right facing direction
			Then moving depending on input
			(W or S = forward or backwards)
			(A or D = Left or Right)
		*/

		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void APlayerCharacter::Jump()
{
	ACharacter::Jump();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Jump"));
}

void APlayerCharacter::PrimaryAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("PrimaryAction"));
}

void APlayerCharacter::Sprint()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Sprint"));
}

void APlayerCharacter::Crouch()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Crouch"));
}