// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphPanelPinFactory.h"

#include "DialogueGraphNode_Dialogue.h"
#include "..\Public\DialogueGraphNode_Base.h"


TSharedPtr<SGraphPin> FDialogueGraphPanelPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	UEdGraphNode* ParentNode = InPin->GetOwningNode();
	if (ParentNode->IsA(UDialogueGraphNode_Base::StaticClass()))
	{
		if (ParentNode->IsA(UDialogueGraphNode_Dialogue::StaticClass()) && InPin->Direction == EGPD_Output)
		{
			
		}
		return SNew(SDialogueGraphPin, InPin);
	}
	// For response nodes, return horizontal box with textblock and pin
	return nullptr;
}
