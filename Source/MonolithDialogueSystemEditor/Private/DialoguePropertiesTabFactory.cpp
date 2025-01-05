// Fill out your copyright notice in the Description page of Project Settings.


#include "DialoguePropertiesTabFactory.h"

#include "DialogueInstance.h"
#include "DialogueInstanceEditorApp.h"


FDialoguePropertiesTabFactory::FDialoguePropertiesTabFactory(TSharedPtr<FDialogueInstanceEditorApp> InApp)
	: FWorkflowTabFactory(FName("DialoguePropertiesTab"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("Properties"));
	ViewMenuDescription = FText::FromString(TEXT("Dialogue Instance Properties"));
	ViewMenuTooltip = FText::FromString(TEXT("Properties"));

	
}

TSharedRef<SWidget> FDialoguePropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<FDialogueInstanceEditorApp> AppSharedPtr = App.Pin();
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bAllowSearch = false;
		DetailsViewArgs.bHideSelectionTip = true;
		DetailsViewArgs.bLockable = false;
		DetailsViewArgs.bSearchInitialKeyFocus = true;
		DetailsViewArgs.bUpdatesFromSelection = false;
		DetailsViewArgs.NotifyHook = nullptr;
		DetailsViewArgs.bShowOptions = true;
		DetailsViewArgs.bShowModifiedPropertiesOption = false;
		DetailsViewArgs.bShowScrollBar = false;
	}

	TSharedPtr<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(AppSharedPtr->GetWorkingDialogueInstance());

	return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			.HAlign(HAlign_Fill)
			[
				DetailsView.ToSharedRef()
			];
}

FText FDialoguePropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("This is the TabToolTip Text for properties"));
}