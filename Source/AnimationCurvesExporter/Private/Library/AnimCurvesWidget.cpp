#include "Library/AnimCurvesWidget.h"
#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "Library/AnimCurves.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

void AnimCurvesWidget::Construct(const FArguments& InArgs)
{
    AnimCurves = NewObject<UAnimCurves>(GetTransientPackage(), UAnimCurves::StaticClass());
    AnimCurves->AddToRoot();

    FPropertyEditorModule& PropModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    FDetailsViewArgs DetailsViewArgs;

    DetailsViewArgs.bHideSelectionTip = true;
    DetailsViewArgs.bLockable = false;
    DetailsViewArgs.bAllowSearch = true;
    DetailsViewArgs.bShowObjectLabel = false;
    DetailsViewArgs.bUpdatesFromSelection = false;
    DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;

    DetailsView = PropModule.CreateDetailView(DetailsViewArgs);

    if (DetailsView.IsValid())
    {
        DetailsView->SetObject(AnimCurves);
    }

    ChildSlot
    [
        SNew(SBox)
        [
            DetailsView.ToSharedRef()
        ]
    ];
}

