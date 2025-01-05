// Copyright Epic Games, Inc. All Rights Reserved.

#include "MonolithDialogueSystemEditor.h"

#include "DialogueInstanceAction.h"
#include "EdGraphUtilities.h"
#include "IAssetTools.h"
#include "SGraphPin.h"

#define LOCTEXT_NAMESPACE "FMonolithDialogueSystemEditorModule"

class SDialogueGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}

protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(0.2f, 1.0f, 0.2f));
	}
};

struct FDialogueGraphPinFactory : public FGraphPanelPinFactory
{
public:
	virtual ~FDialogueGraphPinFactory() {}
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* Pin) const override
	{
		if (FName(TEXT("DialoguePin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueGraphPin, Pin);
		}
		return nullptr;
	}
};

void FMonolithDialogueSystemEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetToolsModule = IAssetTools::Get();
	// TODO: Change to localized text
	EAssetTypeCategories::Type AssetType = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("MonolithDialogueSystem")), FText::FromString("Monolith Dialogue"));
	TSharedPtr<FDialogueInstanceAction> DialogueInstanceAction = MakeShareable(new FDialogueInstanceAction(AssetType));
	AssetToolsModule.RegisterAssetTypeActions(DialogueInstanceAction.ToSharedRef());

	PinFactory = MakeShareable(new FDialogueGraphPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);
}

void FMonolithDialogueSystemEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEdGraphUtilities::UnregisterVisualPinFactory(PinFactory);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMonolithDialogueSystemEditorModule, MonolithDialogueSystemEditor)