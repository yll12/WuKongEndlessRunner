// Fill out your copyright notice in the Description page of Project Settings.


#include "SunWukongCloudComponent.h"
#include "SunWukongCharacter.h"
#include "SunWuKongCloud.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
USunWukongCloudComponent::USunWukongCloudComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SummonCloudTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("SummonCloudTimelineComp"));
	DeactivateTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DeactivateTimelineComp"));

	CanActivateFly = true;
	CanDeactivateFly = false;
}


// Called when the game starts
void USunWukongCloudComponent::BeginPlay()
{
	Super::BeginPlay();

	InitSummonCloudTimelineComp();
	InitDeactivateTimelineComp();

	/* Owner must be a SunWuKongCharacter */
	SunWuKongReference = Cast<ASunWukongCharacter>(GetOwner());

}

// Called every frame
void USunWukongCloudComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USunWukongCloudComponent::ToggleCloud_Implementation(TSubclassOf<ASunWuKongCloud> CloudToSpawn)
{
	if (SunWuKongReference) {
		if (SunWuKongCloudRef && CanDeactivateFly) {
			CanDeactivateFly = false;
			SunWuKongReference->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			SunWuKongReference->Jump();
			SunWuKongReference->GetCloudCollision()->SetRelativeLocation(FVector(0, 0, 0), false, nullptr, ETeleportType::TeleportPhysics);
			SunWuKongCloudRef->AdjustCloudPSToWuKongVelocity = false;
			SunWuKongCloudFinalLocation = AddOffsetToTheFrontRelativeToActor(1500.0f);
			DeactivateTimelineComp->PlayFromStart();
		}
		else if (CanActivateFly) {
			CanActivateFly = false;
			SunWuKongCloudInitialLocation = AddOffsetToTheBackRelativeToActor(800);
			SunWuKongCloudRef = GetWorld()->SpawnActor<ASunWuKongCloud>(CloudToSpawn, SunWuKongCloudInitialLocation, SunWuKongReference->GetActorRotation());
			SunWuKongCloudRef->AttachToComponent(SunWuKongReference->GetCloudPlaceHolder(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			SummonCloudTimelineComp->PlayFromStart();
		}
	}
}

FVector USunWukongCloudComponent::AddOffsetToTheFrontRelativeToActor(float distance)
{
	FVector result = SunWuKongReference->GetActorLocation();
	if (SunWuKongReference->GetActorRotation().Yaw <= -90) {
		result.X -= distance;
	}
	else {
		result.X += distance;
	}

	return result;
}

FVector USunWukongCloudComponent::AddOffsetToTheBackRelativeToActor(float distance)
{
	return AddOffsetToTheFrontRelativeToActor(-distance);
}

void USunWukongCloudComponent::InitSummonCloudTimelineComp()
{
	FOnTimelineFloat UpdateFunctionFloat;
	UpdateFunctionFloat.BindDynamic(this, &USunWukongCloudComponent::UpdateSummonCloud);

	FOnTimelineEvent OnTimelineFinished;
	OnTimelineFinished.BindDynamic(this, &USunWukongCloudComponent::SummonFinished);

	FOnTimelineEvent OnTimelineSpecificTime;
	OnTimelineSpecificTime.BindDynamic(this, &USunWukongCloudComponent::TriggerJump);

	if (SummonCloudTimelineFloatCurve)
	{
		SummonCloudTimelineComp->AddInterpFloat(SummonCloudTimelineFloatCurve, UpdateFunctionFloat);
		SummonCloudTimelineComp->SetTimelineFinishedFunc(OnTimelineFinished);
		SummonCloudTimelineComp->AddEvent(0.1, OnTimelineSpecificTime);
	}
}

void USunWukongCloudComponent::UpdateSummonCloud(float Alpha)
{
	SunWuKongCloudRef->SetActorLocation(
		FMath::Lerp(SunWuKongCloudInitialLocation, 
			SunWuKongReference->GetCloudPlaceHolder()->GetComponentLocation(), Alpha));
}

void USunWukongCloudComponent::SummonFinished()
{
	CanDeactivateFly = true;
	SunWuKongReference->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	SunWuKongCloudRef->AdjustCloudPSToWuKongVelocity = true;
}

void USunWukongCloudComponent::TriggerJump()
{
	if (!SunWuKongReference->GetCharacterMovement()->IsFalling()) {
		SunWuKongReference->Jump();
	}
	SunWuKongReference->GetCloudCollision()->SetRelativeLocation(FVector(0, 0, -130), false, nullptr, ETeleportType::TeleportPhysics);
}

void USunWukongCloudComponent::InitDeactivateTimelineComp()
{
	FOnTimelineFloat UpdateFunctionFloat;
	UpdateFunctionFloat.BindDynamic(this, &USunWukongCloudComponent::UpdateDeactivate);

	FOnTimelineEvent OnTimelineFinished;
	OnTimelineFinished.BindDynamic(this, &USunWukongCloudComponent::DeactivateFinished);

	if (DeactivateTimelineFloatCurve)
	{
		DeactivateTimelineComp->AddInterpFloat(DeactivateTimelineFloatCurve, UpdateFunctionFloat);
		DeactivateTimelineComp->SetTimelineFinishedFunc(OnTimelineFinished);
	}
}

void USunWukongCloudComponent::UpdateDeactivate(float Alpha)
{
	SunWuKongCloudRef->SetActorLocation(
		FMath::Lerp(SunWuKongReference->GetCloudPlaceHolder()->GetComponentLocation(), 
			SunWuKongCloudFinalLocation, Alpha));
}

void USunWukongCloudComponent::DeactivateFinished()
{
	SunWuKongCloudRef->Destroy();
	SunWuKongCloudRef = nullptr;
	CanActivateFly = true;
}