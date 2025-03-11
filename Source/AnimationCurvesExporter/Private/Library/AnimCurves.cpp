#include "Library/AnimCurves.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"
#include "Animation/AnimData/IAnimationDataModel.h"
#include "Animation/AnimSequence.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Modules/ModuleManager.h"

UAnimCurves::UAnimCurves()
{
    OutputDirectory.Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
}

void UAnimCurves::Export()
{
    UE_LOG(LogTemp, Log, TEXT("Export Started."));

    TArray<UAnimSequence*> FinalAnimSequences;

    for (TSoftObjectPtr<UAnimSequence> Ptr : AnimSequences)
    {
        if (UAnimSequence* Anim = Ptr.LoadSynchronous())
        {
            if (!IsValid(Anim)) continue;

            for (const FString& CurveName : CurveNames)
            {
                if (!CurveName.IsEmpty())
                {
                    ExportCurveFromAnim(Anim, CurveName);
                }
            }
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Export Complete."));

    Notify(OutputDirectory.Path);
}

void UAnimCurves::ExportCurveFromAnim(UAnimSequence* AnimSequence, const FString& CurveName) const
{
    if (!AnimSequence) return;

    TArray<float> Times;
    TArray<float> Values;

    const IAnimationDataModel* DataModel = AnimSequence->GetDataModel();
    if (!DataModel) return;

    const FAnimationCurveIdentifier CurveId(FName(CurveName), ERawCurveTrackTypes::RCT_Float);
    if (!DataModel->FindCurve(CurveId)) return;

    const FAnimCurveBase& BaseCurve = DataModel->GetCurve(CurveId);
    const FFloatCurve* FloatCurve = static_cast<const FFloatCurve*>(&BaseCurve);
    if (!FloatCurve) return;

    const FRichCurve& RichCurve = FloatCurve->FloatCurve;

    for (auto It = RichCurve.GetKeyHandleIterator(); It; ++It)
    {
        const FKeyHandle Handle = *It;
        float KeyTime = RichCurve.GetKeyTime(Handle);
        float KeyValue = RichCurve.GetKeyValue(Handle);

        Times.Add(KeyTime);
        Values.Add(KeyValue);
    }

    FString CSVText;
    CSVText.Append(TEXT("Time,Value\n"));

    for (int32 i = 0; i < Times.Num(); ++i)
    {
        CSVText.Append(FString::Printf(TEXT("%.6f,%.6f\n"), Times[i], Values[i]));
    }

    const FString AnimName = AnimSequence->GetName();
    const FString FileName = FString::Printf(TEXT("%s_%s.csv"), *AnimName, *CurveName);
    const FString FullPath = FPaths::Combine(OutputDirectory.Path, FileName);

    IFileManager::Get().MakeDirectory(*OutputDirectory.Path, true);

    if (FFileHelper::SaveStringToFile(CSVText, *FullPath))
    {
        UE_LOG(LogTemp, Log, TEXT("Exported curve '%s' from %s to %s"),
            *CurveName, *AnimName, *FullPath);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to write CSV: %s"), *FullPath);
    }
}

void UAnimCurves::Notify(const FString& DirectoryPath)
{
    FNotificationInfo Info(FText::FromString(TEXT("Export complete!")));

    Info.ExpireDuration = 10.0f;
    Info.bUseThrobber = false;
    Info.bUseSuccessFailIcons = true;
    Info.bFireAndForget = false;
    Info.HyperlinkText = FText::FromString(TEXT("Open Folder"));

    Info.Hyperlink = FSimpleDelegate::CreateLambda([DirectoryPath]()
        {
            FPlatformProcess::LaunchFileInDefaultExternalApplication(*DirectoryPath);
        });

    TSharedPtr<SNotificationItem> NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);

    if (NotificationItem.IsValid())
    {
        NotificationItem->SetCompletionState(SNotificationItem::CS_Success);
        NotificationItem->ExpireAndFadeout();
    }
}



