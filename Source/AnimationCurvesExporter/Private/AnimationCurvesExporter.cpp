#include "AnimationCurvesExporter.h"
#include "ToolMenus.h"
#include "ToolMenuSection.h"
#include "LevelEditor.h"
#include "Framework/Application/SlateApplication.h"
#include "GenericPlatform/GenericApplication.h"
#include "Windows/WindowsApplication.h" 
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/SWindow.h"
#include "Library/AnimCurvesWidget.h"

static const FName AnimationCurvesExporterTabName("AnimationCurvesExporter");

#define LOCTEXT_NAMESPACE "FAnimationCurvesExporterModule"

void FAnimationCurvesExporterModule::StartupModule()
{
    UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAnimationCurvesExporterModule::RegisterMenus)
    );
}

void FAnimationCurvesExporterModule::ShutdownModule()
{
    UToolMenus::UnRegisterStartupCallback(this);
    UToolMenus::UnregisterOwner(this);

    if (ExporterWindow.IsValid())
    {
        ExporterWindow.Pin()->RequestDestroyWindow();
    }
}

void FAnimationCurvesExporterModule::RegisterMenus()
{
    if (UToolMenus* ToolMenus = UToolMenus::Get())
    {
        UToolMenu* Menu = ToolMenus->ExtendMenu("LevelEditor.MainMenu.Tools");
        if (Menu)
        {
            FToolMenuSection& Section = Menu->AddSection("AnimationSection",
                LOCTEXT("AnimationSection", "Animation"));

            Section.AddMenuEntry(
                "OpenAnimationCurvesExporter",
                LOCTEXT("OpenAnimationCurvesExporter_Label", "Anim Curves Exporter"),
                LOCTEXT("OpenAnimationCurvesExporter_Tooltip", "Open the Anim Curves Exporter window"),
                FSlateIcon(),
                FUIAction(FExecuteAction::CreateRaw(this, &FAnimationCurvesExporterModule::OnMenuItemClicked))
            );
        }
    }
}

void FAnimationCurvesExporterModule::OnMenuItemClicked()
{
    TSharedPtr<SWindow> WindowRef = ExporterWindow.Pin();

    if (WindowRef)
    {
        FSlateApplication::Get().SetKeyboardFocus(WindowRef->GetContent(), EFocusCause::SetDirectly);
    }

    TSharedRef<SWindow> Window = SNew(SWindow)
        .Title(LOCTEXT("AnimCurvesExporterWindowTitle", "Animation Curves Exporter"))
        .ClientSize(FVector2D(1000, 800))
        .SupportsMaximize(true)
        .SupportsMinimize(true);

    TSharedRef<AnimCurvesWidget> Widget = SNew(AnimCurvesWidget);

    Window->SetContent(Widget);
    ExporterWindow = Window;

    FSlateApplication::Get().AddWindow(Window);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAnimationCurvesExporterModule, AnimationCurvesExporter)