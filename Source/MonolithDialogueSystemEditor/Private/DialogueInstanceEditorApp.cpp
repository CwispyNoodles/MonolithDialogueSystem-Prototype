#include "DialogueInstanceEditorApp.h"

#include "DialogueGraphSchema.h"
#include "DialogueInstance.h"
#include "DialogueInstanceAppMode.h"
#include "DialogueNode.h"
#include "DialogueNodeInfo.h"
#include "Kismet2/BlueprintEditorUtils.h"

void FDialogueInstanceEditorApp::InitEditor(const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InInitToolkitHost, UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);

	WorkingAsset = Cast<UDialogueInstance>(InObject);
	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph
	(
		WorkingAsset,
		NAME_None,
		UEdGraph::StaticClass(),
		UDialogueGraphSchema::StaticClass()
	);

	InitAssetEditor(
		InMode,
		InInitToolkitHost,
		TEXT("DialogueInstanceEditor"),
		FTabManager::FLayout::NullLayout,
		true, // Create Standalone Menu
		true, // Create Default Toolbar
		ObjectsToEdit
	);

	AddApplicationMode(TEXT("DialogueInstanceAppMode"), MakeShareable(new FDialogueInstanceAppMode(SharedThis(this))));
	SetCurrentMode(TEXT("DialogueInstanceAppMode"));

	UpdateGraphFromWorkingAsset();

	GraphChangedListenerHandle = WorkingGraph->AddOnGraphChangedHandler
	(
		FOnGraphChanged::FDelegate::CreateSP(this, &FDialogueInstanceEditorApp::OnGraphChanged)
	);
}

void FDialogueInstanceEditorApp::OnGraphChanged(const FEdGraphEditAction& EditAction)
{
	UpdateWorkingAssetFromGraph();
}

void FDialogueInstanceEditorApp::SetSelectNodeDetailView(TSharedPtr<IDetailsView> InDetailsView)
{
	SelectedNodeDetailsView = InDetailsView;
	SelectedNodeDetailsView->OnFinishedChangingProperties().AddRaw(this, &FDialogueInstanceEditorApp::OnNodeDetailsViewPropertiesUpdated);
}

void FDialogueInstanceEditorApp::OnGraphSelectionChanged(const FGraphPanelSelectionSet& InSelection)
{
	// Find the first UDialoguenode if any
	for (UObject* Obj : InSelection)
	{
		UDialogueNode* Node = Cast<UDialogueNode>(Obj);
		if (Node)
		{
			SelectedNodeDetailsView->SetObject(Node->GetNodeInfo());
			return;
		}
		SelectedNodeDetailsView->SetObject(nullptr); 
	}
}

void FDialogueInstanceEditorApp::OnNodeDetailsViewPropertiesUpdated(const FPropertyChangedEvent& InEvent)
{
	if (WorkingGraphUi)
	{
		WorkingGraphUi->NotifyGraphChanged();
	}
}

void FDialogueInstanceEditorApp::OnClose()
{
	UpdateWorkingAssetFromGraph();
	WorkingGraph->RemoveOnGraphChangedHandler(GraphChangedListenerHandle);
	FAssetEditorToolkit::OnClose();
}

void FDialogueInstanceEditorApp::UpdateWorkingAssetFromGraph()
{
	if (WorkingGraph == nullptr || WorkingAsset == nullptr)
	{
		return;
	}

	UDialogueRuntimeGraph* RuntimeGraph = NewObject<UDialogueRuntimeGraph>(WorkingAsset);
	WorkingAsset->Graph = RuntimeGraph;

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UDialogueRuntimePin*> IdToPinMap;

	// Record all nodes
	for (auto EditorNode : WorkingGraph->Nodes)
	{
		UDialogueNode* DialogueNode = Cast<UDialogueNode>(EditorNode);
		UDialogueRuntimeNode* RuntimeNode = NewObject<UDialogueRuntimeNode>(RuntimeGraph);
		RuntimeNode->Position = FVector2D(EditorNode->NodePosX, EditorNode->NodePosY);
		RuntimeNode->NodeInfo = DialogueNode->GetNodeInfo();

		// Record all pins connected to EditorNode
		for (auto EditorPin : EditorNode->Pins)
		{
			UDialogueRuntimePin* RuntimePin = NewObject<UDialogueRuntimePin>(RuntimeNode);
			RuntimePin->PinName = EditorPin->PinName;
			RuntimePin->PinId = EditorPin->PinId;

			// Record any connections to output pins
			if (EditorPin->HasAnyConnections() && EditorPin->Direction == EGPD_Output)
			{
				Connections.Add(std::make_pair(EditorPin->PinId, EditorPin->LinkedTo[0]->PinId));
			}

			// Record pin connections in Runtime Node
			IdToPinMap.Add(EditorPin->PinId, RuntimePin);
			if (EditorPin->Direction == EGPD_Input)
			{
				RuntimeNode->InputPin = RuntimePin;
			}
			else
			{
				RuntimeNode->OutputPins.Add(RuntimePin);
			}
		}

		// Record Runtime Nodes to Runtime Graph
		RuntimeGraph->Nodes.Add(RuntimeNode);

		// Set our pin connections
		for (std::pair<FGuid, FGuid> Connection : Connections)
		{
			UDialogueRuntimePin* Pin1 = IdToPinMap[Connection.first];
			UDialogueRuntimePin* Pin2 = IdToPinMap[Connection.second];
			Pin1->Connection = Pin2;
		}
	}
}

void FDialogueInstanceEditorApp::UpdateGraphFromWorkingAsset()
{
	if (WorkingAsset->Graph == nullptr)
	{
		return;
	}

	TArray<std::pair<FGuid, FGuid >> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;

	for (UDialogueRuntimeNode* RuntimeNode : WorkingAsset->Graph->Nodes)
	{
		// Recover Editor Node
		UDialogueNode* NewNode = NewObject<UDialogueNode>(WorkingGraph);
		NewNode->CreateNewGuid();
		NewNode->NodePosX = RuntimeNode->Position.X;
		NewNode->NodePosY = RuntimeNode->Position.Y;

		// Recover Node Info
		if (RuntimeNode->NodeInfo != nullptr)
		{
			NewNode->SetNodeInfo(DuplicateObject(RuntimeNode->NodeInfo, RuntimeNode));
		}
		else
		{
			NewNode->SetNodeInfo(NewObject<UDialogueNodeInfo>(RuntimeNode));
		}

		// Recover Input Pin
		if (RuntimeNode->InputPin != nullptr)
		{
			UDialogueRuntimePin* Pin = RuntimeNode->InputPin;
			UEdGraphPin* EditorPin = NewNode->CreateCustomPin(EGPD_Input, Pin->PinName);
			EditorPin->PinId = Pin->PinId;

			if (Pin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(Pin->PinId, Pin->Connection->PinId));
			}
			IdToPinMap.Add(Pin->PinId, EditorPin);
		}

		// Recover Output Pins
		for (UDialogueRuntimePin* Pin : RuntimeNode->OutputPins)
		{
			UEdGraphPin* EditorPin = NewNode->CreateCustomPin(EGPD_Output, Pin->PinName);
			EditorPin->PinId = Pin->PinId;

			if (Pin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(Pin->PinId, Pin->Connection->PinId));
			}
			IdToPinMap.Add(Pin->PinId, EditorPin);
		}

		WorkingGraph->AddNode(NewNode, true, true);
	}

	// Create links w/o triggering graph modified state
	for (auto Connection : Connections)
	{
		UEdGraphPin* FromPin = IdToPinMap[Connection.first];
		UEdGraphPin* ToPin = IdToPinMap[Connection.second];
		FromPin->LinkedTo.Add(ToPin);
		ToPin->LinkedTo.Add(FromPin);
	}
}

void FDialogueInstanceEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}
