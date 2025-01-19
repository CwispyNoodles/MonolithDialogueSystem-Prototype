// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphPanelNodeFactory.h"

#include "DialogueGraphNode_Alias.h"
#include "DialogueGraphNode_Response.h"
#include "SDialogueGraphNode.h"
#include "SDialogueGraphNode_Alias.h"


TSharedPtr<SGraphNode> FDialogueGraphPanelNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UDialogueGraphNode_Alias* AliasNode = Cast<UDialogueGraphNode_Alias>(Node))
	{
		return SNew(SDialogueGraphNode_Alias, AliasNode);
	}
	if (UDialogueGraphNode_Response* DialogueNode = Cast<UDialogueGraphNode_Response>(Node))
	{
		return SNew(SDialogueGraphNode_Response, DialogueNode);
	}
	
	return nullptr;
}
