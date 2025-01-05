#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class FDialogueInstanceEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{

public:
	void InitEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InInitToolkitHost, UObject* InObject);
	
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
	
};