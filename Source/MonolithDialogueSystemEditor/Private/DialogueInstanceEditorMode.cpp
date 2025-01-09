// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceEditorMode.h"

#include "DialogueGraphTabSummoner.h"
#include "DialogueInstanceEditor.h"


FDialogueInstanceEditorMode::FDialogueInstanceEditorMode(TSharedPtr<FDialogueInstanceEditor> InDialogueInstanceEditor)
	: FApplicationMode(TEXT("FDialogueInstanceEditorMode"))
{
	DialogueInstanceEditor = InDialogueInstanceEditor;
	Tabs.RegisterFactory(MakeShared<FDialogueGraphTabSummoner>(InDialogueInstanceEditor));

	TabLayout = FTabManager::NewLayout("Standalone_DialogueInstanceEditorMode_Layout_v1.0")
	->AddArea
	(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->AddTab(FName(TEXT("DialogueGraphTabId")), ETabState::OpenedTab)
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
