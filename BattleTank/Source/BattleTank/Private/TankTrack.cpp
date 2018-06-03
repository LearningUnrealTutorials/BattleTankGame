// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	m_CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	UStaticMeshComponent *TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack()
{
	FVector AppliedForce = GetForwardVector() * m_CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent *TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(AppliedForce, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle)
{
	m_CurrentThrottle = FMath::Clamp<float>(m_CurrentThrottle + Throttle, -1.0f, 1.0f);
}
