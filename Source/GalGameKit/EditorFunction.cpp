#include "EditorFunction.h"  
#include "Engine/StaticMeshActor.h"  
#include "Components/StaticMeshComponent.h"  
#include "Engine/SceneCapture2D.h"  
#include "Engine/TextureRenderTarget2D.h"  
#include "Materials/MaterialInstanceDynamic.h"  
#include "Kismet/KismetRenderingLibrary.h"  
#include "Engine/World.h"  
#include "Components/SceneCaptureComponent2D.h" // Ensure this header is included  

UMaterialInstanceDynamic* UEditorFunction::GenerateDefaultMaterial(AActor* Actor)
{
    if (!Actor) return nullptr;

    UStaticMeshComponent* StaticMeshComponent = Actor->FindComponentByClass<UStaticMeshComponent>();
    if (!StaticMeshComponent) return nullptr;

    UWorld* World = Actor->GetWorld();
    if (!World) return nullptr;

    // 颜色贴图
    UTextureRenderTarget2D* ColorRT = NewObject<UTextureRenderTarget2D>(World, UTextureRenderTarget2D::StaticClass());
    ColorRT->InitAutoFormat(1024, 1024);

    // 法线贴图
    UTextureRenderTarget2D* NormalRT = NewObject<UTextureRenderTarget2D>(World, UTextureRenderTarget2D::StaticClass());
    NormalRT->InitAutoFormat(1024, 1024);

    // AO贴图（如需自定义材质渲染AO，可在此创建）
    UTextureRenderTarget2D* AORT = NewObject<UTextureRenderTarget2D>(World, UTextureRenderTarget2D::StaticClass());
    AORT->InitAutoFormat(1024, 1024);

    // 捕获颜色
    ASceneCapture2D* ColorCapture = World->SpawnActor<ASceneCapture2D>();
    USceneCaptureComponent2D* ColorComp = ColorCapture->GetCaptureComponent2D();
    ColorComp->TextureTarget = ColorRT;
    ColorComp->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
    ColorComp->ShowOnlyActors.Add(Actor);
    ColorCapture->SetActorLocation(StaticMeshComponent->GetComponentLocation() + FVector(0, 0, 200));
    ColorCapture->SetActorRotation(FRotator(-90, 0, 0));
    ColorComp->CaptureScene();

    // 捕获法线
    ASceneCapture2D* NormalCapture = World->SpawnActor<ASceneCapture2D>();
    USceneCaptureComponent2D* NormalComp = NormalCapture->GetCaptureComponent2D();
    NormalComp->TextureTarget = NormalRT;
    NormalComp->CaptureSource = ESceneCaptureSource::SCS_Normal;
    NormalComp->ShowOnlyActors.Add(Actor);
    NormalCapture->SetActorLocation(StaticMeshComponent->GetComponentLocation() + FVector(0, 0, 200));
    NormalCapture->SetActorRotation(FRotator(-90, 0, 0));
    NormalComp->CaptureScene();

    // AO贴图捕获（需要自定义材质或后处理，示例仅创建RT）
    // 可用自定义材质渲染AO到AORT

    // 加载贴花材质
    UMaterialInterface* DecalMat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/StarterContent/Materials/M_Decal.M_Decal"));
    if (!DecalMat) {
        ColorCapture->Destroy();
        NormalCapture->Destroy();
        return nullptr;
    }

    UMaterialInstanceDynamic* DecalMaterial = UMaterialInstanceDynamic::Create(DecalMat, this);
    DecalMaterial->SetTextureParameterValue(FName("DecalTexture"), ColorRT);
    DecalMaterial->SetTextureParameterValue(FName("NormalTexture"), NormalRT);
    DecalMaterial->SetTextureParameterValue(FName("AOTexture"), AORT); // 需要材质支持AO参数

    ColorCapture->Destroy();
    NormalCapture->Destroy();

    return DecalMaterial;
}
