// Copyright Epic Games, Inc. All Rights Reserved.

#include "MonolithDialogueSystemEditor.h"

#include "DialogueInstanceAction.h"
#include "IAssetTools.h"

#define LOCTEXT_NAMESPACE "FMonolithDialogueSystemEditorModule"

void FMonolithDialogueSystemEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetToolsModule = IAssetTools::Get();
	// TODO: Change to localized text
	EAssetTypeCategories::Type AssetType = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("MonolithDialogueSystem")), FText::FromString("Monolith Dialogue"));
	TSharedPtr<FDialogueInstanceAction> DialogueInstanceAction = MakeShareable(new FDialogueInstanceAction(AssetType));
	AssetToolsModule.RegisterAssetTypeActions(DialogueInstanceAction.ToSharedRef());
}

void FMonolithDialogueSystemEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMonolithDialogueSystemEditorModule, MonolithDialogueSystemEditor)