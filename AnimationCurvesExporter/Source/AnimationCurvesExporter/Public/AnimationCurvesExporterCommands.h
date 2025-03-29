// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AnimationCurvesExporterStyle.h"

class FAnimationCurvesExporterCommands : public TCommands<FAnimationCurvesExporterCommands>
{
public:

	FAnimationCurvesExporterCommands()
		: TCommands<FAnimationCurvesExporterCommands>(TEXT("AnimationCurvesExporter"), NSLOCTEXT("Contexts", "AnimationCurvesExporter", "AnimationCurvesExporter Plugin"), NAME_None, FAnimationCurvesExporterStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};