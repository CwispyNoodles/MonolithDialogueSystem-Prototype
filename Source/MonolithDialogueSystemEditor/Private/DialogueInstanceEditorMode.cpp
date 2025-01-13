// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceEditorMode.h"

#include "DialogueDetailsTabSummoner.h"
#include "DialogueGraphTabSummoner.h"
#include "DialogueInstanceEditor.h"


FDialogueInstanceEditorMode::FDialogueInstanceEditorMode(TSharedPtr<FDialogueInstanceEditor> InDialogueInstanceEditor)
	: FApplicationMode(TEXT("FDialogueInstanceEditorMode"))
{
	DialogueInstanceEditor = InDialogueInstanceEditor;
	Tabs.RegisterFactory(MakeShared<FDialogueGraphTabSummoner>(InDialogueInstanceEditor));
	Tabs.RegisterFactory(MakeShared<FDialogueDetailsTabSummoner>(InDialogueInstanceEditor));

	TabLayout = FTabManager::NewLayout("Standalone_DialogueInstanceEditorMode_Layout_v1.1")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewSplitter()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.75f)
				->AddTab(FName(TEXT("DialogueGraphTabId")), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.25f)
				->AddTab(FName(TEXT("DialogueDetailsTabId")), ETabState::OpenedTab)
			)
		)
	);
	
}

void FDialogueInstanceEditorMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FDialogueInstanceEditor> Editor = DialogueInstanceEditor.Pin();
	Editor->PushTabFactories(Tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FDialogueInstanceEditorMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void FDialogueInstanceEditorMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
