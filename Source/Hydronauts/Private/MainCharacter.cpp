#include "MainCharacter.h"
#include "HydroSaveGame.h"
#include "SharkAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	LastCheckpointLocation = GetActorLocation();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::FMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::FLook);
	}
}

void AMainCharacter::FMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMainCharacter::FLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMainCharacter::Jumping()
{
	Jump();
}

void AMainCharacter::SaveGame()
{
	UHydroSaveGame* SaveGameInstance = Cast<UHydroSaveGame>(UGameplayStatics::CreateSaveGameObject(UHydroSaveGame::StaticClass()));
	SaveGameInstance->WorldLocation = GetActorLocation();
	SaveGameInstance->WorldRotation = GetActorRotation();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SlotName, SaveGameInstance->SlotIndex);
}

void AMainCharacter::LoadGame()
{
	UHydroSaveGame* LoadGameInstance = Cast<UHydroSaveGame>(UGameplayStatics::CreateSaveGameObject(UHydroSaveGame::StaticClass()));
	LoadGameInstance = Cast<UHydroSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SlotName, LoadGameInstance->SlotIndex));
	SetActorLocation(LoadGameInstance->WorldLocation);
	SetActorRotation(LoadGameInstance->WorldRotation);
}

void AMainCharacter::RespawnAtCheckpoint()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->DisableInput(PC);
	}

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, [this, PC]()
		{
			SetActorLocation(LastCheckpointLocation);
			GetCharacterMovement()->Velocity = FVector::ZeroVector;

			if (PC)
			{
				PC->EnableInput(PC);
			}

		}, 2.0f, false);
}
