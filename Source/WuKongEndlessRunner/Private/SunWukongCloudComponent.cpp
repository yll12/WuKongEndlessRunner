// Fill out your copyright notice in the Description page of Project Settings.


#include "SunWukongCloudComponent.h"
#include "SunWukongCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
USunWukongCloudComponent::USunWukongCloudComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RotationTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("RotationTimelineComp"));
}


// Called when the game starts
void USunWukongCloudComponent::BeginPlay()
{
	Super::BeginPlay();

	InitRotationTimelineComp();

	AActor* owner = GetOwner();

	sunWuKongReference = Cast<ASunWukongCharacter>(owner);

}


// Called every frame
void USunWukongCloudComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USunWukongCloudComponent::ToggleCloud_Implementation(TSubclassOf<class AActor> ClassToSpawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Toggling"));
	if (SunWuKongCloudRef) {
		SunWuKongCloudRef = nullptr;
	}
	else {
		if (CanActivateFly) {
			CanActivateFly = false;
			FVector SpawnLocation;
			if (sunWuKongReference->GetActorRotation().Yaw <= -90) {
				SpawnLocation = sunWuKongReference->GetActorLocation();
				SpawnLocation.X = SpawnLocation.X + 800;
			}
			else {
				SpawnLocation = sunWuKongReference->GetActorLocation();
				SpawnLocation.X = SpawnLocation.X - 800;
			}
			SunWuKongCloudInitialLocation = SpawnLocation;
			SunWuKongCloudRef = GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnLocation, sunWuKongReference->GetActorRotation());
			SunWuKongCloudRef->AttachToComponent(sunWuKongReference->GetCloudPlaceHolder(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			RotationTimelineComp->PlayFromStart();

		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Toggling Finished"));
}

void USunWukongCloudComponent::InitRotationTimelineComp()
{
	FOnTimelineFloat UpdateFunctionFloat;
	UpdateFunctionFloat.BindDynamic(this, &USunWukongCloudComponent::UpdateRelativeRotation);

	FOnTimelineEvent OnTimelineFinished;
	OnTimelineFinished.BindDynamic(this, &USunWukongCloudComponent::RotateFinished);

	FOnTimelineEvent OnTimelineSpecificTime;
	OnTimelineSpecificTime.BindDynamic(this, &USunWukongCloudComponent::TriggerJump);

	if (RotateTimelineFloatCurve)
	{
		RotationTimelineComp->AddInterpFloat(RotateTimelineFloatCurve, UpdateFunctionFloat);
		RotationTimelineComp->SetTimelineFinishedFunc(OnTimelineFinished);
		RotationTimelineComp->AddEvent(0.1, OnTimelineSpecificTime);
	}
}

void USunWukongCloudComponent::UpdateRelativeRotation(float Alpha)
{
	UE_LOG(LogTemp, Warning, TEXT("Testing %f"), Alpha);
	SunWuKongCloudRef->SetActorLocation(FMath::Lerp(SunWuKongCloudInitialLocation, sunWuKongReference->GetCloudPlaceHolder()->GetComponentLocation(), Alpha));
}

void USunWukongCloudComponent::RotateFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("Testing!"));
	CanDeactivateFly = true;
	sunWuKongReference->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	UE_LOG(LogTemp, Warning, TEXT("Finished!"));
}

void USunWukongCloudComponent::TriggerJump()
{
	UE_LOG(LogTemp, Warning, TEXT("Triggering Jump!"));
	sunWuKongReference->GetCloudCollision()->SetRelativeLocation(FVector(0, 0, -130), false, nullptr, ETeleportType::TeleportPhysics);
	sunWuKongReference->Jump();
}