// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimationCurvesExporterStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FAnimationCurvesExporterStyle::StyleInstance = nullptr;

void FAnimationCurvesExporterStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FAnimationCurvesExporterStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FAnimationCurvesExporterStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("AnimationCurvesExporterStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FAnimationCurvesExporterStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("AnimationCurvesExporterStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("AnimationCurvesExporter")->GetBaseDir() / TEXT("Resources"));

	Style->Set("AnimationCurvesExporter.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FAnimationCurvesExporterStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FAnimationCurvesExporterStyle::Get()
{
	return *StyleInstance;
}
