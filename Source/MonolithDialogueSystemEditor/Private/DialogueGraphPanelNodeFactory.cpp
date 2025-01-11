// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphPanelNodeFactory.h"

#include "DialogueGraphNode_Alias.h"


TSharedPtr<SGraphNode> FDialogueGraphPanelNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UDialogueGraphNode_Alias* AliasNode = Cast<UDialogueGraphNode_Alias>(Node))
	{
		
	}
	return nullptr;
}
