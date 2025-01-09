// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class FDialogueInstanceEditor;
/**
 * 
 */
class FDialogueInstanceEditorMode : public FApplicationMode
{
public:
 FDialogueInstanceEditorMode(TSharedPtr<FDialogueInstanceEditor> InDialogueInstanceEditor);

private:
 TWeakPtr<FDialogueInstanceEditor> DialogueInstanceEditor;
 FWorkflowAllowedTabSet Tabs;

public: // FApplicationMode Interface
 virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
 virtual void PreDeactivateMode() override;
 virtual void PostActivateMode() override;
};
