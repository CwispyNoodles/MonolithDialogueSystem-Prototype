// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstanceEditor.h"

#include "DialogueGraph.h"
#include "DialogueGraphNode_Alias.h"
#include "DialogueGraphNode_Query.h"
#include "DialogueGraphNode_Response.h"
#include "DialogueGraphNode_Root.h"
#include "..\Public\DialogueGraphNode_Base.h"
#include "DialogueInstance.h"
#include "DialogueInstanceEditorMode.h"
#include "DialogueGraphSchema.h"
#include "..\..\MonolithDialogueSystemRuntime\Public\DialogueNodeData_Base.h"
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

	BindGraphCommands();

	DialogueGraphPanelNodeFactory = MakeShareable(new FDialogueGraphPanelNodeFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(DialogueGraphPanelNodeFactory);

	DialogueGraphPanelPinFactory = MakeShareable(new FDialogueGraphPanelPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(DialogueGraphPanelPinFactory);

	WorkingAsset = Cast<UDialogueInstance>(InObject);
	WorkingAsset->SetPreSaveListener([this] () { OnWorkingAssetPreSave(); });
	
	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph
	(
		WorkingAsset,
		NAME_None,
		UDialogueGraph::StaticClass(),
		UDialogueGraphSchema::StaticClass()
	);

	UDialogueGraph* DialogueGraph = Cast<UDialogueGraph>(WorkingGraph);
	DialogueGraph->DialogueGraphData = NewObject<UDialogueGraphData>(WorkingGraph);

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

	LoadGraph();
}

void FDialogueInstanceEditor::SetSelectedNodeDetailsView(TSharedPtr<IDetailsView> DetailsView)
{
	SelectedNodeDetailsView = DetailsView;
	SelectedNodeDetailsView->OnFinishedChangingProperties().AddRaw(this, &FDialogueInstanceEditor::OnNodeDetailViewPropertiesUpdated);
}

void FDialogueInstanceEditor::OnGraphSelectionChanged(const FGraphPanelSelectionSet& Selection)
{
	if (UDialogueGraphNode_Base* SelectedNode = GetSelectedNode(Selection))
	{
		SelectedNodeDetailsView->SetObject(SelectedNode->GetDialogueNodeData());
	}
	else
	{
		SelectedNodeDetailsView->SetObject(nullptr);
	}
}

void FDialogueInstanceEditor::OnWorkingAssetPreSave()
{
	SaveGraph();
}

void FDialogueInstanceEditor::BindGraphCommands()
{
	ToolkitCommands->MapAction(FGenericCommands::Get().Delete,
		FExecuteAction::CreateRaw(this, &FDialogueInstanceEditor::DeleteSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FDialogueInstanceEditor::CanDeleteNodes));
}

void FDialogueInstanceEditor::DeleteSelectedNodes()
{
	if (!WorkingGraphEditor.IsValid())
	{
		return;
	}

	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

	WorkingGraphEditor->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = WorkingGraphEditor->GetSelectedNodes();
	WorkingGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		UEdGraphNode* EdNode = Cast<UEdGraphNode>(*NodeIt);
		if (EdNode == nullptr || !EdNode->CanUserDeleteNode())
			continue;;

		if (UDialogueGraphNode_Base* EdNode_Node = Cast<UDialogueGraphNode_Base>(EdNode))
		{
			EdNode_Node->Modify();

			const UEdGraphSchema* Schema = EdNode_Node->GetSchema();
			if (Schema != nullptr)
			{
				Schema->BreakNodeLinks(*EdNode_Node);
			}

			EdNode_Node->DestroyNode();
		}
		else
		{
			EdNode->Modify();
			EdNode->DestroyNode();
		}
	}
}

bool FDialogueInstanceEditor::CanDeleteNodes()
{
	// If any of the nodes can be deleted then we should allow deleting
	const FGraphPanelSelectionSet SelectedNodes = WorkingGraphEditor->GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node != nullptr && Node->CanUserDeleteNode())
		{
			return true;
		}
	}

	return false;
}

void FDialogueInstanceEditor::OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& Event)
{
	if (WorkingGraphEditor)
	{
		if (UDialogueGraphNode_Base* Node = GetSelectedNode(WorkingGraphEditor->GetSelectedNodes()))
		{
			Node->OnPropertiesChanged();
		}
		WorkingGraphEditor->NotifyGraphChanged();
		
	}
}

UDialogueGraphNode_Base* FDialogueInstanceEditor::GetSelectedNode(const FGraphPanelSelectionSet& Selection)
{
	for (UObject* Obj : Selection)
	{
		if (UDialogueGraphNode_Base* Node = Cast<UDialogueGraphNode_Base>(Obj))
		{
			return Node;
		}
	}
	return nullptr;
}

void FDialogueInstanceEditor::SaveGraph()
{
	if (!WorkingAsset || !WorkingGraph)
	{
		return;
	}

	UDialogueRuntimeGraph* RuntimeGraph = NewObject<UDialogueRuntimeGraph>(WorkingAsset);
	WorkingAsset->Graph = RuntimeGraph;

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UDialogueRuntimePin*> IdToPinMap;

	for (UEdGraphNode* EditorNode : WorkingGraph->Nodes)
	{
		UDialogueRuntimeNode* RuntimeNode = NewObject<UDialogueRuntimeNode>(RuntimeGraph);
		RuntimeNode->Position = FVector2D(EditorNode->NodePosX, EditorNode->NodePosY);

		for (UEdGraphPin* EditorPin : EditorNode->Pins)
		{
			UDialogueRuntimePin* RuntimePin = NewObject<UDialogueRuntimePin>(RuntimeNode);
			RuntimePin->PinName = EditorPin->PinName;
			RuntimePin->PinId = EditorPin->PinId;
			RuntimePin->Parent = RuntimeNode;
			RuntimePin->Direction = EditorPin->Direction;

			if (EditorPin->HasAnyConnections())
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(EditorPin->PinId, EditorPin->LinkedTo[0]->PinId);
				Connections.Add(Connection);
			}

			IdToPinMap.Add(EditorPin->PinId, RuntimePin);
			if (RuntimePin->Direction == EGPD_Input)
			{
				RuntimeNode->InputPin = RuntimePin;
			}
			else
			{
				RuntimeNode->OutputPins.Add(RuntimePin);
			}
		}
		UDialogueGraphNode_Base* EditorDialogueNode = Cast<UDialogueGraphNode_Base>(EditorNode);
		RuntimeNode->NodeData = DuplicateObject(EditorDialogueNode->GetDialogueNodeData(), RuntimeNode);
		RuntimeNode->NodeType = EditorDialogueNode->GetDialogueNodeType();

		RuntimeGraph->Nodes.Add(RuntimeNode);

		if (EditorNode->IsA(UDialogueGraphNode_Root::StaticClass()))
		{
			RuntimeGraph->RootNode = RuntimeNode;
		}

		if (UDialogueGraphNode_Alias_Out* Alias_Out = Cast<UDialogueGraphNode_Alias_Out>(EditorNode))
		{
			RuntimeGraph->AliasToOutputMap.Add(Alias_Out->GetAliasOutData()->AliasName.ToString(), RuntimeNode);
		}
	}

	for (std::pair<FGuid, FGuid> Connection : Connections)
	{
		UDialogueRuntimePin* Pin1 = IdToPinMap[Connection.first];
		UDialogueRuntimePin* Pin2 = IdToPinMap[Connection.second];
		Pin1->Connection = Pin2;
	}
}

void FDialogueInstanceEditor::LoadGraph()
{
	if (!WorkingAsset->Graph)
	{
		UDialogueRuntimeGraph* RuntimeGraph = NewObject<UDialogueRuntimeGraph>(WorkingAsset);
		WorkingGraph->GetSchema()->CreateDefaultNodesForGraph(*WorkingGraph);
		WorkingAsset->Graph = RuntimeGraph;
		return;
	}

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;

	for (UDialogueRuntimeNode* RuntimeNode : WorkingAsset->Graph->Nodes)
	{
		UDialogueGraphNode_Base* EditorNode = nullptr;
		switch (RuntimeNode->NodeType)
		{
		case EDialogueNodeType::Root:
			EditorNode = NewObject<UDialogueGraphNode_Root>(WorkingGraph);
			break;
		case EDialogueNodeType::Query:
			EditorNode = NewObject<UDialogueGraphNode_Query>(WorkingGraph);
			break;
		case EDialogueNodeType::Response:
			EditorNode = NewObject<UDialogueGraphNode_Response>(WorkingGraph);
			break;
		case EDialogueNodeType::AliasIn:
			EditorNode = NewObject<UDialogueGraphNode_Alias_In>(WorkingGraph);
			break;
		case EDialogueNodeType::AliasOut:
			EditorNode = NewObject<UDialogueGraphNode_Alias_Out>(WorkingGraph);
			break;
		default: ;
			continue;
		}

		EditorNode->CreateNewGuid();
		EditorNode->SetPosition(RuntimeNode->Position);

		if (RuntimeNode->NodeData)
		{
			EditorNode->SetDialogueNodeData(DuplicateObject(RuntimeNode->NodeData, EditorNode));
		}
		else
		{
			EditorNode->InitializeNodeData();
		}

		if (RuntimeNode->InputPin)
		{
			UDialogueRuntimePin* InputPin = RuntimeNode->InputPin;
			FName Category = TEXT("Inputs");
			UEdGraphPin* EditorPin = EditorNode->CreatePin(InputPin->Direction, Category, InputPin->PinName);
			EditorPin->PinId = InputPin->PinId;

			if (InputPin->Connection)
			{
				Connections.Add(std::make_pair(InputPin->PinId, InputPin->Connection->PinId));
			}
			IdToPinMap.Add(InputPin->PinId, EditorPin);
		}

		for (UDialogueRuntimePin* RuntimePin : RuntimeNode->OutputPins)
		{
			FName Category = TEXT("Outputs");
			UEdGraphPin* EditorPin = EditorNode->CreatePin(RuntimePin->Direction, Category, RuntimePin->PinName);
			EditorPin->PinId = RuntimePin->PinId;

			if (RuntimePin->Connection)
			{
				Connections.Add(std::make_pair(RuntimePin->PinId, RuntimePin->Connection->PinId));
			}
			IdToPinMap.Add(RuntimePin->PinId, EditorPin);
		}
		WorkingGraph->AddNode(EditorNode, true, true);
	}
	for (std::pair<FGuid, FGuid> Connection : Connections)
	{
		UEdGraphPin* FromPin = IdToPinMap[Connection.first];
		UEdGraphPin* ToPin = IdToPinMap[Connection.second];
		FromPin->LinkedTo.Add(ToPin);
		ToPin->LinkedTo.Add(FromPin);
	}
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

void FDialogueInstanceEditor::OnClose()
{
	SaveGraph();
	WorkingAsset->SetPreSaveListener(nullptr);
	FWorkflowCentricApplication::OnClose();
}

#undef LOCTEXT_NAMESPACE
