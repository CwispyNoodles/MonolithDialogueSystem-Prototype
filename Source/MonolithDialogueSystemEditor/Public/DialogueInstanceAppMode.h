// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class FDialogueInstanceEditorApp;

class FDialogueInstanceAppMode : public FApplicationMode
{
public:
	FDialogueInstanceAppMode(TSharedPtr<FDialogueInstanceEditorApp> InApp);

private:
	TWeakPtr<FDialogueInstanceEditorApp> App;

	// List of all Tab factories relevant to this Application Mode
	FWorkflowAllowedTabSet Tabs;

public: // FApplicationMode Interface
	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;
};
