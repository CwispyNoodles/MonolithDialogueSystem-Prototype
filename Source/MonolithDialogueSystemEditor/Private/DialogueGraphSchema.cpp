// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphSchema.h"

#include "DialogueGraph.h"
#include "DialogueGraphNode_Alias.h"
#include "DialogueGraphNode_Query.h"
#include "DialogueGraphNode_Response.h"
#include "DialogueGraphNode_Root.h"

UEdGraphNode* FDialogueGraphSchemaAction_NewNode::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UDialogueGraph* DialogueGraph = Cast<UDialogueGraph>(ParentGraph);
	if (!DialogueGraph)
	{
		return nullptr;
	}
	UDialogueGraphNode* MyNode = NewObject<UDialogueGraphNode>(ParentGraph, ClassTemplate);
	MyNode->CreateNewGuid();
	MyNode->SetPosition(Location);

	MyNode->AllocateDefaultPins();

	DialogueGraph->Modify();
	DialogueGraph->AddNodeExplicit(MyNode, true, true);

	return MyNode;
}

void UDialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	FGraphNodeCreator<UDialogueGraphNode_Root> NodeCreator(Graph);
	UDialogueGraphNode_Root* MyNode = NodeCreator.CreateNode(true, UDialogueGraphNode_Root::StaticClass());
	NodeCreator.Finalize();
	SetNodeMetaData(MyNode, FNodeMetadata::DefaultGraphNode);
	
}

void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FDialogueGraphSchemaAction_NewNode> NewQueryNodeAction(
		new FDialogueGraphSchemaAction_NewNode(
			UDialogueGraphNode_Query::StaticClass(),
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New Query Node")),
			FText::FromString(TEXT("Creates new Query Node")),
			FText::GetEmpty(),
			0));

		TSharedPtr<FDialogueGraphSchemaAction_NewNode> NewResponseNodeAction(
		new FDialogueGraphSchemaAction_NewNode(
			UDialogueGraphNode_Response::StaticClass(),
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New Response Node")),
			FText::FromString(TEXT("Creates new Response Node")),
			FText::GetEmpty(),
			0));

	ContextMenuBuilder.AddAction(NewQueryNodeAction);
	ContextMenuBuilder.AddAction(NewResponseNodeAction);

	if (const UDialogueGraph* DialogueGraph = Cast<UDialogueGraph>(ContextMenuBuilder.CurrentGraph))
	{
		if (DialogueGraph->bCreateNodeTest)
		{
			TSharedPtr<FDialogueGraphSchemaAction_NewNode> NewAliasNodeAction(
				new FDialogueGraphSchemaAction_NewNode(
					UDialogueGraphNode_Alias_In::StaticClass(),
					FText::FromString(TEXT("Nodes")),
					FText::FromString(TEXT("New Alias Node")),
					FText::FromString(TEXT("Creates new Alias Node")),
					FText::GetEmpty(),
					0));

			ContextMenuBuilder.AddAction(NewAliasNodeAction);
		}
	}
}
