// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomMoveCube.generated.h"

UCLASS()
class RANDOMMOVEEVENT_API ARandomMoveCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomMoveCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle MoveTimerHandle;

	int32 CurrentStep = 1;
	int32 MaxStep = 10;

	FVector StartLocation;
	int32 EventCount = 0;
	double TotalDistance = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//Turn, Move  함수 추가
	virtual void Move(double  Forward, double Right);
	virtual void Turn(double Rotation);
	//랜덤하게 이벤트가 발생하는 함수 추가
	virtual bool RandomEvent();
	//10회 이동 시 마다 Move,Turn, RandomEvent, 좌표 로그 출력 등 로직 동작 함수
	virtual void DoRandomStep();


};
