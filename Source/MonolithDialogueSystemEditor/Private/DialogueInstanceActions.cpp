// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceActions.h"

#include "DialogueInstance.h"

#define LOCTEXT_NAMESPACE "DialogueInstanceActions"

DialogueInstanceActions::DialogueInstanceActions(EAssetTypeCategories::Type InAssetCategory)
	: AssetCategory(InAssetCategory)
{
}

FText DialogueInstanceActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "DialogueInstanceActions", "Dialogue Instance");
}

FColor DialogueInstanceActions::GetTypeColor() const
{
	return FColor::Emerald;
}

UClass* DialogueInstanceActions::GetSupportedClass() const
{
	return UDialogueInstance::StaticClass();
}

void DialogueInstanceActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if (UDialogueInstance* DialogueInstance = Cast<UDialogueInstance>(*ObjIt))
		{
			
		}
	}
}

uint32 DialogueInstanceActions::GetCategories()
{
	return AssetCategory;
}

#undef LOCTEXT_NAMESPACE