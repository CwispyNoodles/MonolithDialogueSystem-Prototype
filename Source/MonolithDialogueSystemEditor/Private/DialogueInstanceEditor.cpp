﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceEditor.h"

#include "DialogueGraph.h"
#include "DialogueGraphNode.h"
#include "DialogueInstance.h"
#include "DialogueInstanceEditorMode.h"
#include "DialogueGraphSchema.h"
#include "DialogueNodeData.h"
#include "GraphEditorActions.h"
#include "Framework/Commands/GenericCommands.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "AssetEditor_GenericGraph"

const FName DialogueInstanceEditorAppName = FName(TEXT("DialogueInstanceEditorApp"));

void FDialogueInstanceEditor::InitDialogueInstanceEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);

	FGenericCommands::Register();
	FGraphEditorCommands::Register();

	DialogueGraphPanelNodeFactory = MakeShareable(new FDialogueGraphPanelNodeFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(DialogueGraphPanelNodeFactory);

	DialogueGraphPanelPinFactory = MakeShareable(new FDialogueGraphPanelPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(DialogueGraphPanelPinFactory);

	WorkingAsset = Cast<UDialogueInstance>(InObject);
	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph
	(
		WorkingAsset,
		NAME_None,
		UDialogueGraph::StaticClass(),
		UDialogueGraphSchema::StaticClass()
	);

	WorkingGraph->GetSchema()->CreateDefaultNodesForGraph(*WorkingGraph);

	bool bCreateDefaultStandaloneMenu = true;
	bool bCreateDefaultToolBar = true;
	InitAssetEditor
	(
		Mode,
		InitToolkitHost,
		DialogueInstanceEditorAppName,
		FTabManager::FLayout::NullLayout,
		bCreateDefaultStandaloneMenu,
		bCreateDefaultToolBar,
		ObjectsToEdit
	);

	AddApplicationMode(TEXT("FDialogueInstanceEditorMode"), MakeShareable(new FDialogueInstanceEditorMode(SharedThis(this))));
	SetCurrentMode(TEXT("FDialogueInstanceEditorMode"));
}

void FDialogueInstanceEditor::SetSelectedNodeDetailsView(TSharedPtr<IDetailsView> DetailsView)
{
	SelectedNodeDetailsView = DetailsView;
	SelectedNodeDetailsView->OnFinishedChangingProperties().AddRaw(this, &FDialogueInstanceEditor::OnNodeDetailViewPropertiesUpdated);
}

void FDialogueInstanceEditor::OnGraphSelectionChanged(const FGraphPanelSelectionSet& Selection)
{
	if (UDialogueGraphNode* SelectedNode = GetSelectedNode(Selection))
	{
		SelectedNodeDetailsView->SetObject(SelectedNode);
	}
	else
	{
		SelectedNodeDetailsView->SetObject(nullptr);
	}
}

void FDialogueInstanceEditor::OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& Event)
{
	if (WorkingGraphEditor)
	{
		if (UDialogueGraphNode* Node = GetSelectedNode(WorkingGraphEditor->GetSelectedNodes()))
		{
			Node->OnPropertiesChanged();
		}
		WorkingGraphEditor->NotifyGraphChanged();
		
	}
}

UDialogueGraphNode* FDialogueInstanceEditor::GetSelectedNode(const FGraphPanelSelectionSet& Selection)
{
	for (UObject* Obj : Selection)
	{
		if (UDialogueGraphNode* Node = Cast<UDialogueGraphNode>(Obj))
		{
			return Node;
		}
	}
	return nullptr;
}

void FDialogueInstanceEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

FName FDialogueInstanceEditor::GetToolkitFName() const
{
	return FName("FDialogueInstanceEditor");
}

FText FDialogueInstanceEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Dialogue Instance Editor");
}

FString FDialogueInstanceEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("DialogueInstanceEditor");
}

FLinearColor FDialogueInstanceEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FDialogueInstanceEditor::GetDocumentationLink() const
{
	return TEXT("https://github.com/CwispyNoodles/MonolithDialogueSystem-v1");
}

void FDialogueInstanceEditor::OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit)
{
	
}

void FDialogueInstanceEditor::OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit)
{
	
}

#undef LOCTEXT_NAMESPACE