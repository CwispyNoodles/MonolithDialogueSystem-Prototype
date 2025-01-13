// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FDialogueInstanceEditor;
/**
 * 
 */
class FDialogueDetailsTabSummoner : public FWorkflowTabFactory
{
public:
	FDialogueDetailsTabSummoner(TSharedPtr<FDialogueInstanceEditor> InDialogueInstanceEditor);

private:
	TWeakPtr<FDialogueInstanceEditor> DialogueInstanceEditor;
 
public: // FWorkflowTabFactory Interface
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;
};
