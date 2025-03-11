#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UAnimCurves;

class AnimCurvesWidget : public SCompoundWidget
{

public:

    SLATE_BEGIN_ARGS(AnimCurvesWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);

    UAnimCurves* AnimCurves;
    TSharedPtr<IDetailsView> DetailsView;
    
};
