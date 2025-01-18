// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\DialogueGraphNode_Base.h"

#include "..\..\MonolithDialogueSystemRuntime\Public\DialogueNodeData_Base.h"

void UDialogueGraphNode_Base::SetPosition(FVector2D InPos)
{
	NodePosX = InPos.X;
	NodePosY = InPos.Y;
}

void UDialogueGraphNode_Base::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialog Node Actions")));
	UDialogueGraphNode_Base* node = (UDialogueGraphNode_Base*)this;
	Section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda(
			[node] () {
				node->GetGraph()->RemoveNode(node);
			}
		))
	);
}

void UDialogueGraphNode_Base::InitializeNodeData()
{
	if (NodeDataClass)
	{
		DialogueNodeData = NewObject<UDialogueNodeData_Base>(this, NodeDataClass);
	}
	else
	{
		DialogueNodeData = NewObject<UDialogueNodeData_Base>(this);
	}
}
