// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphPanelNodeFactory.h"

#include "DialogueGraphNode_Alias.h"
#include "DialogueGraphNode_Query.h"
#include "..\Public\SDialogueGraphNode_Query.h"
#include "SDialogueGraphNode_Alias.h"


TSharedPtr<SGraphNode> FDialogueGraphPanelNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UDialogueGraphNode_Alias* AliasNode = Cast<UDialogueGraphNode_Alias>(Node))
	{
		return SNew(SDialogueGraphNode_Alias, AliasNode);
	}
	if (UDialogueGraphNode_Query* DialogueNode = Cast<UDialogueGraphNode_Query>(Node))
	{
		return SNew(SDialogueGraphNode_Query, DialogueNode);
	}
	
	return nullptr;
}
