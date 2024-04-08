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
    
    void MoveForward(float Value);
    
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MaxSpeed;
    
    UPROPERTY(EditAnywhere, Category = "Movement")
    float AccelerationRate;
    
    UPROPERTY(EditAnywhere, Category = "Movement")
    float DecelerationRate;
    
    void EntregarPaquete();
    
    void GolpeCoche();
    
    void RecogerComida();

    void ActivateNitro();

    void DeactivateNitro();

    UPROPERTY(EditAnywhere, Category = "Delibers")
    int32 EntregasRestantes;

    float NitroSpeed;

    bool bIsNitroActive;

    float NitroTimeElapsed;
    float NitroDuration;
    bool QuedaNitro;
protected:
    virtual void BeginPlay() override;
    
    int32 PaquetesRestantes;
    

private:
    float CurrentSpeed;
    
    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    
};