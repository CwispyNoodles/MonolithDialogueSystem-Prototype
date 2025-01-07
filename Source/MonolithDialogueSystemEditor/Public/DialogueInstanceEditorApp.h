#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class UDialogueInstance;

class FDialogueInstanceEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{

public:
	void InitEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InInitToolkitHost, UObject* InObject);
	UDialogueInstance* GetWorkingDialogueInstance() const { return WorkingAsset; }
	UEdGraph* GetWorkingGraph() { return WorkingGraph; }
	void OnGraphChanged(const FEdGraphEditAction& EditAction);
	void SetWorkingGraphUi(TSharedPtr<SGraphEditor> InWorkingGraphUi) { WorkingGraphUi = InWorkingGraphUi; }
	void SetSelectNodeDetailView(TSharedPtr<IDetailsView> InDetailsView);
	void OnGraphSelectionChanged(const FGraphPanelSelectionSet& InSelection);
	void OnNodeDetailsViewPropertiesUpdated(const FPropertyChangedEvent& InEvent);

private:
	UPROPERTY()
	UDialogueInstance* WorkingAsset = nullptr;

	UPROPERTY()
	UEdGraph* WorkingGraph = nullptr;

	TSharedPtr<SGraphEditor> WorkingGraphUi = nullptr;
	TSharedPtr<IDetailsView> SelectedNodeDetailsView = nullptr;

	FDelegateHandle GraphChangedListenerHandle;

protected:
	void UpdateWorkingAssetFromGraph();
	void UpdateGraphFromWorkingAsset();
	
public: // FWorkflowCentricApplication Interface
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

public: // FAssetEditorToolkit interface
	virtual FName GetToolkitFName() const override { return FName(TEXT("DialogueInstanceEditorApp")); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString(TEXT("DialogueInstanceEditorApp")); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("DialogueInstanceEditorApp"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f); }
	virtual FString GetDocumentationLink() const override { return TEXT("https://github.com/CwispyNoodles"); }
	virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override { }
	virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override { }

	virtual void OnClose() override;
	
};