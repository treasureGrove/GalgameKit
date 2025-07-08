// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundDecal.h"
#include "Engine/World.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AGroundDecal::AGroundDecal()
{
    PrimaryActorTick.bCanEverTick = false;
    
    // 初始化贴花组件
    GridDecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("GridDecalComponent"));
    RootComponent = GridDecalComponent;

	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetupAttachment(RootComponent);
	SceneCapture->bCaptureEveryFrame = false; // 只在需要时捕捉
	SceneCapture->bCaptureOnMovement = false; // 禁止在移动时捕捉
	RenderTarget->CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("RenderTarget"));
	RenderTarget->InitAutoFormat(1024, 1024); // 设置渲染目标的分辨率
	SceneCapture->TextureTarget = RenderTarget;
}

// Called when the game starts or when spawned
void AGroundDecal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGroundDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AGroundDecal::SpawnGridDecal(const FVector& Location, const FVector& Normal)
{
    if (!SourceMesh || !DecalMaterial || !GridDecalComponent)
        return;
    
    // 计算贴花的变换矩阵
    FTransform DecalTransform = CalculateDecalTransform(Location, Normal);
    
    // 设置贴花位置和旋转
    GridDecalComponent->SetWorldTransform(DecalTransform);
    
    // 设置贴花材质
    GridDecalComponent->SetDecalMaterial(DecalMaterial);
    
    // 根据网格大小计算贴花尺寸
    FBox MeshBounds = GetMeshBounds();
    FVector DecalExtent = MeshBounds.GetExtent() * (DecalSize / 100.0f);
    GridDecalComponent->DecalSize = DecalExtent;
    
    // 启用贴花渲染
    GridDecalComponent->SetVisibility(true);
}
FBox AGroundDecal::GetMeshBounds() const
{
    if (!SourceMesh)
    {
        return FBox(FVector(-50.0f), FVector(50.0f)); // 默认边界框
    }
    
    // 获取静态网格的边界框
    FBoxSphereBounds MeshBounds = SourceMesh->GetBounds();
    return FBox(MeshBounds.Origin - MeshBounds.BoxExtent, 
                MeshBounds.Origin + MeshBounds.BoxExtent);
}

FTransform AGroundDecal::CalculateDecalTransform(const FVector& Location, const FVector& Normal) const
{
    // 计算贴花的朝向
    FVector ForwardVector = Normal;
    FVector RightVector = FVector::CrossProduct(Normal, FVector::UpVector).GetSafeNormal();
    
    // 如果法向量与上向量平行，使用前向量作为参考
    if (RightVector.IsNearlyZero())
    {
        RightVector = FVector::CrossProduct(Normal, FVector::ForwardVector).GetSafeNormal();
    }
    
    FVector UpVector = FVector::CrossProduct(RightVector, ForwardVector).GetSafeNormal();
    
    // 创建旋转矩阵
    FMatrix RotationMatrix = FMatrix(RightVector, UpVector, ForwardVector, FVector::ZeroVector);
    FQuat DecalRotation = RotationMatrix.ToQuat();
    
    // 稍微偏移位置避免Z-fighting
    FVector DecalLocation = Location + Normal * 0.1f;
    
    return FTransform(DecalRotation, DecalLocation, FVector::OneVector);
}

void AGroundDecal::BakeMeshToDecalTexture(const FVector& location, const FVector& Normal)
{
    UStaticMeshComponent* TempMeshComp = NewObject<UStaticMeshComponent>(this);
    TempMeshComp->RegisterComponent();
    TempMeshComp->SetStaticMesh(SourceMesh);
    TempMeshComp->SetWorldLocation(location);
    TempMeshComp->SetWorldRotation(Normal.Rotation());

    // 设置SceneCapture的位置和朝向
    SceneCapture->SetWorldLocation(location + Normal * 100.0f); // 适当偏移
    SceneCapture->SetWorldRotation(Normal.Rotation());

    // 只渲染TempMeshComp
    SceneCapture->ShowOnlyComponents.Empty();
    SceneCapture->ShowOnlyComponents.Add(TempMeshComp);

    // 捕捉一次
    SceneCapture->CaptureScene();

    // 清理临时组件
    TempMeshComp->DestroyComponent();
}
