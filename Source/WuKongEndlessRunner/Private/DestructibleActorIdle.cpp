// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleActorIdle.h"
#include "DestructibleComponent.h"

// Sets default values
ADestructibleActorIdle::ADestructibleActorIdle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootSceneComponent->SetupAttachment(RootComponent);
	RootComponent = RootSceneComponent;

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleComponent"));
	DestructibleComponent->SetupAttachment(RootSceneComponent);
	DestructibleComponent->SetEnableGravity(false);

	Tags.Add(FName("Enemy"));
}

// Called when the game starts or when spawned
void ADestructibleActorIdle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleActorIdle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleActorIdle::HitReact_Implementation(AActor* damageCauser, const struct FImpactParticleSystemStruct& impactParticleSystem)
{
	HitReactSpawnDestructibleActor();
	DestructibleComponent->SetVisibility(false);
	DestructibleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	HitReactPlayGetHit(impactParticleSystem);
	DestroyActorAfterDelay(5);
}

void ADestructibleActorIdle::DestroyActorAfterDelay(float delay)
{
	FTimerHandle UnusedHandle;
	FTimerDelegate Delegate;
	Delegate.BindLambda([this] { Destroy(); });
	GetWorld()->GetTimerManager().SetTimer(
		UnusedHandle, Delegate, delay, false);
}