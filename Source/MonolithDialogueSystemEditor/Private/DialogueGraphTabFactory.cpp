// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphTabFactory.h"
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
	return SNew(STextBlock).Text(FText::FromString(TEXT("This is a test")));
}

FText FDialogueGraphTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("This is the TabToolTip Text"));
}
