// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceAction.h"

#include "DialogueInstance.h"


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
	// TODO 
}

uint32 FDialogueInstanceAction::GetCategories()
{
	return AssetCategory;
}
