// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceAppMode.h"

#include "DialogueGraphTabFactory.h"
#include "DialogueInstanceEditorApp.h"
#include "DialoguePropertiesTabFactory.h"


FDialogueInstanceAppMode::FDialogueInstanceAppMode(TSharedPtr<FDialogueInstanceEditorApp> InApp)
	: FApplicationMode(TEXT("DialogueInstanceAppMode"))
{
	App = InApp;
	Tabs.RegisterFactory(MakeShareable(new FDialogueGraphTabFactory(InApp)));
	Tabs.RegisterFactory(MakeShareable(new FDialoguePropertiesTabFactory(InApp)));
	
	TabLayout = FTabManager::NewLayout("DialogueInstanceAppMode_Layout_v2")
	->AddArea(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewSplitter()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.75)
				->AddTab(FName(TEXT("DialogueGraphTab")), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.25)
				->AddTab(FName(TEXT("DialoguePropertiesTab")), ETabState::OpenedTab)
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
