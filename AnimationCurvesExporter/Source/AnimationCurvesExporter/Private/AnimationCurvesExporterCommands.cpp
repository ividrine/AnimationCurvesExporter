// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimationCurvesExporterCommands.h"

#define LOCTEXT_NAMESPACE "FAnimationCurvesExporterModule"

void FAnimationCurvesExporterCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "AnimationCurvesExporter", "Bring up AnimationCurvesExporter window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
