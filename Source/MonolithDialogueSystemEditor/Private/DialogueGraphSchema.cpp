// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueGraphSchema.h"

#include "DialogueNode.h"
#include "DialogueNodeInfo.h"


UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D MouseLocation, bool bSelectNewNode)
{
	UDialogueNode* Result = NewObject<UDialogueNode>(ParentGraph);
	Result->CreateNewGuid();
	Result->NodePosX = MouseLocation.X;
	Result->NodePosY = MouseLocation.Y;
	Result->SetNodeInfo(NewObject<UDialogueNodeInfo>(Result));

	Result->CreateCustomPin
	(
		EGPD_Input,
		TEXT("SomeInput")
	);

	Result->CreateCustomPin
	(
		EGPD_Output,
		TEXT("SomeOutput")
	);

	ParentGraph->Modify();
	ParentGraph->AddNode(Result, true, true);

	return Result;
	
}

void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	TSharedPtr<FNewNodeAction> NewNodeAction
	(
		new FNewNodeAction
		(
		FText::FromString(TEXT("Nodes")),
		FText::FromString(TEXT("New Node")),
		FText::FromString(TEXT("Makes a new node")),
		0
		)
	);

	ContextMenuBuilder.AddAction(NewNodeAction);
}

const FPinConnectionResponse UDialogueGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A == nullptr || B == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Need 2 pins"));
	}
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Inputs can only connect to outputs"));
	}
	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT(""));
}
