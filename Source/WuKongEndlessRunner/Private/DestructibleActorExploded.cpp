// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleActorExploded.h"
#include "Engine.h"
#include "DestructibleComponent.h"

// Sets default values
ADestructibleActorExploded::ADestructibleActorExploded()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootSceneComponent->SetupAttachment(RootComponent);
	RootComponent = RootSceneComponent;

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleComponent"));
	DestructibleComponent->SetupAttachment(RootSceneComponent);
	DestructibleComponent->SetEnableGravity(false);

	// This didn't work - since DestructibleComponent is deprecated, will just create BP_ADestructibleActorExploded with these changes
//	DestructibleComponent->SetCollisionProfileName(TEXT("Custom"));
//	DestructibleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
//	DestructibleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

}

// Called when the game starts or when spawned
void ADestructibleActorExploded::BeginPlay()
{
	Super::BeginPlay();
	DestructibleComponent->ApplyRadiusDamage(5, GetActorLocation(), 0, 50000.0f, true);
	DestroyActorAfterDelay(5);
}

void ADestructibleActorExploded::DestroyActorAfterDelay(float delay)
{
	FTimerHandle UnusedHandle;
	FTimerDelegate Delegate;
	Delegate.BindLambda([this] { Destroy(); });
	GetWorld()->GetTimerManager().SetTimer(
		UnusedHandle, Delegate, delay, false);
}

// Called every frame
void ADestructibleActorExploded::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

