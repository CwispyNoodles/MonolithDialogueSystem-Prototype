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

	SGraphEditor::FGraphEditorEvents GraphEvents;
	GraphEvents.OnSelectionChanged.BindRaw(AppSharedPtr.Get(), &FDialogueInstanceEditorApp::OnGraphSelectionChanged);

	TSharedPtr<SGraphEditor> GraphEditor =
		SNew(SGraphEditor)
		.IsEditable(true)
		.GraphEvents(GraphEvents)
		.GraphToEdit(AppSharedPtr->GetWorkingGraph());
	AppSharedPtr->SetWorkingGraphUi(GraphEditor);
	return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			.HAlign(HAlign_Fill)
			[
				GraphEditor.ToSharedRef()
			];
}

FText FDialogueGraphTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("This is the TabToolTip Text"));
}
