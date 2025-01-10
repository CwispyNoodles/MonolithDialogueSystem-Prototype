// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraph.h"

void UDialogueGraph::AddNode(UEdGraphNode* NodeToAdd, bool bUserAction, bool bSelectNewNode)
{
	Super::AddNode(NodeToAdd, bUserAction, bSelectNewNode);
	
}

void UDialogueGraph::AddNodeExplicit(UEdGraphNode* NodeToAdd, bool bUserAction, bool bSelectNewNode)
{
	AddNode(NodeToAdd, bUserAction, bSelectNewNode);
	bCreateNodeTest = true;
}
