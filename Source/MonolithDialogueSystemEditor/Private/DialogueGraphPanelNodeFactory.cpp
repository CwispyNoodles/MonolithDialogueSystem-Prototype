// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphPanelNodeFactory.h"

#include "DialogueGraphNode_Alias.h"
#include "DialogueGraphNode_Dialogue.h"
#include "SDialogueGraphNode.h"
#include "SDialogueGraphNode_Alias.h"


TSharedPtr<SGraphNode> FDialogueGraphPanelNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UDialogueGraphNode_Alias* AliasNode = Cast<UDialogueGraphNode_Alias>(Node))
	{
		return SNew(SDialogueGraphNode_Alias, AliasNode);
	}
	if (UDialogueGraphNode_Dialogue* DialogueNode = Cast<UDialogueGraphNode_Dialogue>(Node))
	{
		return SNew(SDialogueGraphNode, DialogueNode);
	}
	
	return nullptr;
}
