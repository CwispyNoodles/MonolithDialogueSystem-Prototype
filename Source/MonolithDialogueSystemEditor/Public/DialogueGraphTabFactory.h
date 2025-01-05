// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FDialogueInstanceEditorApp;

class FDialogueGraphTabFactory : public FWorkflowTabFactory
{
public:
	FDialogueGraphTabFactory(TSharedPtr<FDialogueInstanceEditorApp> InApp);

private:
	TWeakPtr<FDialogueInstanceEditorApp> App; 

public: // FWorkflowTabFactory Interface
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;
};