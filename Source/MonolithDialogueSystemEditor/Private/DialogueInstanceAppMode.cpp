// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceAppMode.h"

#include "DialogueGraphTabFactory.h"
#include "DialogueInstanceEditorApp.h"


FDialogueInstanceAppMode::FDialogueInstanceAppMode(TSharedPtr<FDialogueInstanceEditorApp> InApp)
	: FApplicationMode(TEXT("DialogueInstanceAppMode"))
{
	App = InApp;
	Tabs.RegisterFactory(MakeShareable(new FDialogueGraphTabFactory(InApp)));
	TabLayout = FTabManager::NewLayout("DialogueInstanceAppMode_Layout_v1")
	->AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewStack()
			->AddTab(
				FName(TEXT("DialogueGraphTab")), ETabState::OpenedTab
			)
		)
	);
}

void FDialogueInstanceAppMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	TSharedPtr<FDialogueInstanceEditorApp> AppSharedPtr = App.Pin();
	AppSharedPtr->PushTabFactories(Tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FDialogueInstanceAppMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void FDialogueInstanceAppMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
