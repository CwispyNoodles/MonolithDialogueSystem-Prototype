// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceAction.h"

#include "DialogueInstance.h"
#include "DialogueInstanceEditorApp.h"


FDialogueInstanceAction::FDialogueInstanceAction(EAssetTypeCategories::Type InAssetCategory)
{
	AssetCategory = InAssetCategory;
}

FText FDialogueInstanceAction::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_DialogueInstance", "Dialogue Instance");
}

FColor FDialogueInstanceAction::GetTypeColor() const
{
	return FColor::Cyan;
}

UClass* FDialogueInstanceAction::GetSupportedClass() const
{
	return UDialogueInstance::StaticClass();
}

void FDialogueInstanceAction::OpenAssetEditor(const TArray<UObject*>& inObjects,
	TSharedPtr<IToolkitHost> editWithinLevelEditor)
{
	EToolkitMode::Type Mode = editWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto Object : inObjects)
	{
		if (UDialogueInstance* DialogueInstance = Cast<UDialogueInstance>(Object))
		{
			TSharedRef<FDialogueInstanceEditorApp> Editor(new FDialogueInstanceEditorApp());
			Editor->InitEditor(Mode, editWithinLevelEditor, DialogueInstance);
		}
		
	}
}

uint32 FDialogueInstanceAction::GetCategories()
{
	return AssetCategory;
}
