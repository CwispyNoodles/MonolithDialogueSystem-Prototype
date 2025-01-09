// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class UDialogueInstance;
/**
 * 
 */
class MONOLITHDIALOGUESYSTEMEDITOR_API FDialogueInstanceEditor : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{

public:
	void InitDialogueInstanceEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject);

	UDialogueInstance* GetWorkingAsset() { return WorkingAsset; }
	UEdGraph* GetWorkingGraph() { return WorkingGraph; }
private:
	UDialogueInstance* WorkingAsset = nullptr;
	UEdGraph* WorkingGraph = nullptr;
	
public: // FAssetEditorToolkit interface
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
    virtual FName GetToolkitFName() const override;
    virtual FText GetBaseToolkitName() const override;
    virtual FString GetWorldCentricTabPrefix() const override;
    virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetDocumentationLink() const override;
	virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override;
	virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override;
};
