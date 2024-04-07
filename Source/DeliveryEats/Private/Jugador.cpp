// Fill out your copyright notice in the Description page of Project Settings.


#include "Jugador.h"
#include "Engine.h"


// Sets default values
AJugador::AJugador()
{
	// Set default values for movement properties
	MaxSpeed = 1000.f;
	AccelerationRate = 500.f;
	DecelerationRate = 1000.f;
	CurrentSpeed = 0.f;

	// Set initial number of packages
	PaquetesRestantes = 10;
	EntregasRestantes = 5;

	NitroSpeed = 1500.f;
	bIsNitroActive = false;

	NitroTimeElapsed = 0;
	NitroDuration = 5;
	QuedaNitro = true;
}

// Called when the game starts or when spawned
void AJugador::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AJugador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Apply movement
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * CurrentSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	if (bIsNitroActive == true)
	{
		NitroTimeElapsed += DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("TiempoNitro: %d"), NitroTimeElapsed);
		
		if (NitroTimeElapsed >= NitroDuration)
		{
			QuedaNitro = false;
		}
	}
	
	
}

// Called to bind functionality to input
void AJugador::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement inputs
	PlayerInputComponent->BindAxis("MoveForward", this, &AJugador::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJugador::AddControllerYawInput);

	PlayerInputComponent->BindAction("Nitro", IE_Pressed, this, &AJugador::ActivateNitro);
	PlayerInputComponent->BindAction("Nitro", IE_Released, this, &AJugador::DeactivateNitro);


	// Bind collision function to overlap event
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AJugador::OnOverlapBegin);
}

void AJugador::ActivateNitro()
{
	if(QuedaNitro == true)
	{
		bIsNitroActive = true;
	}
	if(QuedaNitro == false)
	{
		bIsNitroActive = false;
	}
	
}

void AJugador::DeactivateNitro()
{
	bIsNitroActive = false;
}
// Function to handle forward movement
void AJugador::MoveForward(float Value)
{
	if (Value != 0.f)
	{
		// Verificar si el nitro está activo
		if (bIsNitroActive == true)
		{
			// Utilizar la velocidad de nitro si está activo
			CurrentSpeed = FMath::Clamp(CurrentSpeed + (Value * NitroSpeed * GetWorld()->GetDeltaSeconds()), 0.f, NitroSpeed);
		}
		if (bIsNitroActive == false)
		{
			// Utilizar la lógica de movimiento normal si el nitro no está activo
			CurrentSpeed = FMath::Clamp(CurrentSpeed + (Value * AccelerationRate * GetWorld()->GetDeltaSeconds()), 0.f, MaxSpeed);
		}
	}
	else
	{
		// Decelerar si no se está moviendo hacia adelante
		CurrentSpeed = FMath::Clamp(CurrentSpeed - (DecelerationRate * GetWorld()->GetDeltaSeconds()), 0.f, MaxSpeed);
	}
}

// Collision function called when player collides with other actors
void AJugador::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is tagged as "Entrega"
	if (OtherActor && OtherActor->ActorHasTag("Entrega"))
	{
		// Call EntregarPaquete function
		EntregarPaquete();
		UE_LOG(LogTemp, Warning, TEXT("El jugador ha entregado una pizza"));
	}

	if (OtherActor && OtherActor->ActorHasTag("Coche"))
	{
		// Destroy the player
		UE_LOG(LogTemp, Warning, TEXT("El jugador ha chocado con un enemigo"));
		GolpeCoche();

	}

	if (OtherActor && OtherActor->ActorHasTag("Pizzeria"))
	{
		// Destroy the player
		UE_LOG(LogTemp, Warning, TEXT("El jugador ha recogido mas comida"));
		RecogerComida();

	}

	if (OtherActor && OtherActor->ActorHasTag("Gasolina"))
	{
		// Destroy the player
		UE_LOG(LogTemp, Warning, TEXT("El jugador llena el depósito"));
		//Rellenar Gasoline();

	}
}

// Function to handle package delivery
void AJugador::EntregarPaquete()
{
	// Verificar si hay paquetes restantes
	if (PaquetesRestantes > 0)
	{
		// Implement your package delivery logic here
		UE_LOG(LogTemp, Warning, TEXT("Entrega de paquete realizada"));
        
		// Reduce the number of remaining packages
		PaquetesRestantes--;

		UE_LOG(LogTemp, Warning, TEXT("Paquetes restantes: %d"), PaquetesRestantes);
		

		EntregasRestantes--;
		if (EntregasRestantes == 0)
		{
			// Cambiar a la escena MainMenu
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
		}
	}
	else
	{
		// Si no hay paquetes restantes, registrar un mensaje de advertencia
		UE_LOG(LogTemp, Warning, TEXT("No hay paquetes restantes para entregar"));
	}
}

// Function to handle package delivery
void AJugador::GolpeCoche()
{
	
	// Reduce the number of remaining packages by 3
	PaquetesRestantes -= 3;

	// Ensure the number of remaining packages doesn't go below 0
	PaquetesRestantes = FMath::Max(PaquetesRestantes, 0);

	UE_LOG(LogTemp, Warning, TEXT("Paquetes restantes: %d"), PaquetesRestantes);

	Jump();


	
}

// Function to handle package delivery
void AJugador::RecogerComida()
{
	PaquetesRestantes += 8;
	
	PaquetesRestantes = FMath::Max(PaquetesRestantes, 0);

	UE_LOG(LogTemp, Warning, TEXT("Paquetes restantes: %d"), PaquetesRestantes);
}

