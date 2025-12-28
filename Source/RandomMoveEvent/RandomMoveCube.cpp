// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomMoveCube.h"
#include "Engine/Engine.h"

// Sets default values
ARandomMoveCube::ARandomMoveCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARandomMoveCube::BeginPlay()
{
	Super::BeginPlay();
	//시작 점 (0,50,0)으로 위치 설정
	StartLocation = FVector(0.f, 50.f, 0.f);
	SetActorLocation(StartLocation);

	//이벤트 발생 횟수 및 스텝 수, 총 이동 거리 초기화
	CurrentStep = 1;
	EventCount = 0;
	TotalDistance = 0.f;

	//For,While문으로 처리할 경우 1 프레임 내에서 For문 다 돌아가 버려서 제대로 움직임 동작 불가
	// 월드의 타이머 매니저와 타이머를 설정
	//0.5초마다 현재 액터에 DoRandomStep 호출하는 식으로 반복문 처리
	GetWorld()->GetTimerManager().SetTimer(
		MoveTimerHandle,
		this,
		&ARandomMoveCube::DoRandomStep,
		0.5f,
		true
	);

}

// Called every frame
void ARandomMoveCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARandomMoveCube::Move(double  Forward, double Right) {
	//랜덤 범위 내 로케이션 벡터
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Forward;
	NewLocation += GetActorRightVector() * Right;

	SetActorLocation(NewLocation);
}

void ARandomMoveCube::Turn(double Rotation) {
	//랜덤 범위 내 로테이션 벡터 만들기
	SetActorRotation(FRotator(0.f, Rotation, 0.f));
}

bool ARandomMoveCube::RandomEvent()
{
	//1~100 숫자 중 뽑힌 숫자가 50이상이면 확률 50프로
	int32 RandomNum = FMath::RandRange(1, 100);

	if (RandomNum >= 50)
	{
		//랜덤 이벤트 발생여부 출력
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				2.f,
				FColor::Red,
				TEXT("Random Event Occur")
			);
		}
		return true;
	}
	else {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				2.f,
				FColor::Red,
				TEXT("Random Event Doesn't Occur")
			);
		}
		return false;
	}


}

void ARandomMoveCube::DoRandomStep()
{
	// 현재 스텝이 10번 됬는지 체크 후 총 이동 거리, 총 이벤트 발생 횟수 출력
	if (CurrentStep > MaxStep)
	{
		GetWorld()->GetTimerManager().ClearTimer(MoveTimerHandle);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::White,
				FString::Printf(
					TEXT("Total Moved Distance: %.2f, Random Event Count: %d"),
					TotalDistance,
					EventCount
				)
			);
		}
		return;
	}

	//랜덤 이동 X좌표, Y좌표, 회전 각 초기화
	double RandomForward = FMath::RandRange(-500, 500);
	double RandomRight   = FMath::RandRange(-500, 500);
	double RandomRotation = FMath::RandRange(0, 360);
	//매 스텝마다 거리 계산위해 이동 전 좌표, 이동 후 좌표 설정
	//이동 거리 계산값 TotalDistance에 더함
	FVector BeforeLocation = GetActorLocation();
	Turn(RandomRotation);
	Move(RandomForward, RandomRight);
	//이동 거리 누적
	const FVector PresentLocation = GetActorLocation();
	TotalDistance += FVector::Distance(BeforeLocation, PresentLocation);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Green,
			FString::Printf(TEXT("Step %d : Location (X: %.1f, Y: %.1f, Z: %.1f)"), CurrentStep,GetActorLocation().X, GetActorLocation().Y,GetActorLocation().Z)
		);
	}
	//랜덤 이벤트 발생 시 이벤트 발생횟수 더하기
	if (RandomEvent())
	{
		EventCount++;
	}

	//현재 스텝수 업데이트
	CurrentStep++;
}

