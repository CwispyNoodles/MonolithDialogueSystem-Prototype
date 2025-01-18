// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphPanelPinFactory.h"

#include "..\Public\DialogueGraphNode_Base.h"


TSharedPtr<SGraphPin> FDialogueGraphPanelPinFactory::CreatePin(UEdGraphPin* InPin) const
{
	if (InPin->GetOwningNode()->IsA(UDialogueGraphNode_Base::StaticClass()))
	{
		return SNew(SDialogueGraphPin, InPin);
	}
	return nullptr;
}
