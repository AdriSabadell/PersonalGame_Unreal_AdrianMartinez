// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Jugador.generated.h"

UCLASS()
class DELIVERYEATS_API AJugador : public ACharacter
{
	GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AJugador();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Function to handle forward movement
    void MoveForward(float Value);

    // Maximum forward speed
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MaxSpeed;

    // Acceleration rate
    UPROPERTY(EditAnywhere, Category = "Movement")
    float AccelerationRate;

    // Deceleration rate
    UPROPERTY(EditAnywhere, Category = "Movement")
    float DecelerationRate;

    // Function to handle package delivery
    void EntregarPaquete();

    // Function to handle package delivery
    void GolpeCoche();

    // Function to handle package delivery
    void RecogerComida();

    void ActivateNitro();

    void DeactivateNitro();

    UPROPERTY(EditAnywhere, Category = "Delibers")
    int32 EntregasRestantes;

    float NitroSpeed;

    bool bIsNitroActive;

    int32 NitroTimeElapsed;
    int32 NitroDuration;
    bool QuedaNitro;
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Number of packages to deliver
    int32 PaquetesRestantes;
    

private:
    // Current forward speed
    float CurrentSpeed;

    // Collision function called when player collides with other actors
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    
};