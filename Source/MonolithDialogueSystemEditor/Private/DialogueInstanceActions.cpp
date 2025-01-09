// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceActions.h"

#include "DialogueInstance.h"
#include "DialogueInstanceEditor.h"

#define LOCTEXT_NAMESPACE "DialogueInstanceActions"

FDialogueInstanceActions::FDialogueInstanceActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText FDialogueInstanceActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "DialogueInstanceActions", "Dialogue Instance");
}

FColor FDialogueInstanceActions::GetTypeColor() const
{
	return FColor::Emerald;
}

UClass* FDialogueInstanceActions::GetSupportedClass() const
{
	return UDialogueInstance::StaticClass();
}

void FDialogueInstanceActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UDialogueInstance* DialogueInstance = Cast<UDialogueInstance>(*ObjIt))
		{
			TSharedRef<FDialogueInstanceEditor> NewGraphEditor(new FDialogueInstanceEditor());
			NewGraphEditor->InitDialogueInstanceEditor(Mode, EditWithinLevelEditor, DialogueInstance);
		}
	}
}

uint32 FDialogueInstanceActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE