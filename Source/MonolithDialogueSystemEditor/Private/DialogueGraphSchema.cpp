// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphSchema.h"

#include "DialogueGraphNode_Root.h"

void UDialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	FGraphNodeCreator<UDialogueGraphNode_Root> NodeCreator(Graph);
	UDialogueGraphNode_Root* MyNode = NodeCreator.CreateNode(true, UDialogueGraphNode_Root::StaticClass());
	NodeCreator.Finalize();
	SetNodeMetaData(MyNode, FNodeMetadata::DefaultGraphNode);
}
