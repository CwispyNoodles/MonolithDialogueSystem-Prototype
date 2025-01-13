// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueDetailsTabSummoner.h"

#include "DialogueInstance.h"
#include "DialogueInstanceEditor.h"

#define LOCTEXT_NAMESPACE "DialogueDetailsTabSummoner"

const FName DialogueDetailsTabId = FName(TEXT("DialogueDetailsTabId"));

FDialogueDetailsTabSummoner::FDialogueDetailsTabSummoner(TSharedPtr<FDialogueInstanceEditor> InDialogueInstanceEditor)
	: FWorkflowTabFactory(DialogueDetailsTabId, InDialogueInstanceEditor)
{
	DialogueInstanceEditor = InDialogueInstanceEditor;
	TabLabel = LOCTEXT("DialogueDetailsTabLabel", "Details");
	ViewMenuDescription = LOCTEXT("DialogueDetails_ViewMenu_Desc", "Details");
	ViewMenuTooltip = LOCTEXT("DialogueDetails_ViewMenu_ToolTip", "Show the Details");
}

TSharedRef<SWidget> FDialogueDetailsTabSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<FDialogueInstanceEditor> Editor = DialogueInstanceEditor.Pin();
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

	TSharedPtr<IDetailsView> SelectedNodeDetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	SelectedNodeDetailsView->SetObject(nullptr);
	Editor->SetSelectedNodeDetailsView(SelectedNodeDetailsView);

	return SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.HAlign(HAlign_Fill)
				[
					SelectedNodeDetailsView.ToSharedRef()
				];
}

FText FDialogueDetailsTabSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FWorkflowTabFactory::GetTabToolTipText(Info);
}

#undef LOCTEXT_NAMESPACE