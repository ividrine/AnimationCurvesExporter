#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AnimCurves.generated.h"

UCLASS()
class ANIMATIONCURVESEXPORTER_API UAnimCurves : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, Category = "Export", meta = (AbsolutePath))
    FDirectoryPath OutputDirectory;

    UPROPERTY(EditAnywhere, Category = "Export")
    TArray<TSoftObjectPtr<UAnimSequence>> AnimSequences;

    UPROPERTY(EditAnywhere, Category = "Export")
    TArray<FString> CurveNames;

public:
    UAnimCurves();

    /** Called from the details panel (CallInEditor) to run the export logic. */
    UFUNCTION(CallInEditor, Category = "Export")
    void Export();

private:
    /** Helper to do the actual curve extraction logic. */
    void ExportCurveFromAnim(UAnimSequence* AnimSequence, const FString& CurveName) const;

    void Notify(const FString& DirectoryPath);

};
