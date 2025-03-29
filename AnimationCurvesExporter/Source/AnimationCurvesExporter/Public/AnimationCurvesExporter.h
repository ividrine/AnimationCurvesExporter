// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FAnimationCurvesExporterModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void RegisterMenus();
    void OnMenuItemClicked();

    TWeakPtr<class SWindow> ExporterWindow;

    TSharedPtr<class FUICommandList> PluginCommands;
	
};
