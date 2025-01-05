// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphTabFactory.h"

#include "DialogueInstance.h"
#include "DialogueInstanceEditorApp.h"

FDialogueGraphTabFactory::FDialogueGraphTabFactory(TSharedPtr<FDialogueInstanceEditorApp> InApp)
	: FWorkflowTabFactory(FName("DialogueGraphTab"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString(TEXT("Dialogue Graph"));
	ViewMenuDescription = FText::FromString(TEXT("Displays the Dialogue Graph View."));
	ViewMenuTooltip = FText::FromString(TEXT("Show the Dialogue Graph"));

	
}

TSharedRef<SWidget> FDialogueGraphTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
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

FText FDialogueGraphTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("This is the TabToolTip Text"));
}
