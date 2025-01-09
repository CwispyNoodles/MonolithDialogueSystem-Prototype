// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class FDialogueInstanceActions : public FAssetTypeActions_Base
{
public:
	FDialogueInstanceActions(EAssetTypeCategories::Type InAssetCategory);

private:
	EAssetTypeCategories::Type AssetCategory;

public: // FAssetTypeActions_Base Interface
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;
};
