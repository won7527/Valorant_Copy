// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//박스 콜라이더 컴포넌트 생성
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component")); //생성자로 콜리전
	//생성한 박스 콜라이더 컴포넌트를 최상단 컴포넌트로 설정한다
	SetRootComponent(BoxComp);
	//스태틱 메시 컴포넌트를 생성한다
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Static Mesh"));
	//박스 콜라이더 컴포넌트의 자식 컴포넌트로 설정한다
	meshComp->SetupAttachment(BoxComp);
	//박스 콜라이더의 크기를 50 50 50으로 설정한다
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	BoxComp->SetBoxExtent(boxSize);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//사용자의 입력키 이용
	//1.상하 입력값과 좌우 입력값을 이용해서 방향백터를 만든다.
	FVector dir = FVector(0, h, v);

	//2. 방향백터의 길이가 1이 되도록 정규화 한다.
	dir.Normalize();

	//3.이동할 위치 좌표를 구한다(p=p0+vt)
	FVector nowLocation = GetActorLocation() + dir * moveSpeed * DeltaTime;

	//4.현재 액터의 위치 좌표를 앞에서 구한 새 좌표로 갱신한다.
	SetActorLocation(nowLocation);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis 바인딩된 값을 함수에 연결한다.
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawn::moveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawn::moveVertical);

}

void APlayerPawn::moveHorizontal(float value) {
	h = value;
}

void APlayerPawn::moveVertical(float value) {
	v = value;
}


