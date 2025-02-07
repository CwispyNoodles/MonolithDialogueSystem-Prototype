﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SDialogueGraphNode_Alias.h"

#include "DialogueGraphNode_Alias.h"
#include "DialogueNodeData_Alias.h"


void SDialogueGraphNode_Alias::Construct(const FArguments& InArgs, UDialogueGraphNode_Alias* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
	
}

FText SDialogueGraphNode_Alias::GetAliasName() const
{
	// UDialogueGraphNode_Alias* AliasNode = Cast<UDialogueGraphNode_Alias>(GraphNode);
	// check(AliasNode);
	//
	// UDialogueNodeData_Alias_In* NodeData = Cast<UDialogueNodeData_Alias_In>(AliasNode->GetDialogueNodeData());
	// return NodeData->AliasName;

	if (UDialogueGraphNode_Alias_In* Alias_In = Cast<UDialogueGraphNode_Alias_In>(GraphNode))
	{
		return Cast<UDialogueNodeData_Alias_In>(Alias_In->GetDialogueNodeData())->AliasName;
	}

	if (UDialogueGraphNode_Alias_Out* Alias_Out = Cast<UDialogueGraphNode_Alias_Out>(GraphNode))
	{
		return Cast<UDialogueNodeData_Alias_Out>(Alias_Out->GetDialogueNodeData())->AliasName;
	}
	return FText();
}

void SDialogueGraphNode_Alias::UpdateGraphNode()
{
	SGraphNode::UpdateGraphNode();
}

TSharedRef<SWidget> SDialogueGraphNode_Alias::CreateNodeContentArea()
{
	// NODE CONTENT AREA
	return SNew(SBorder)
		.BorderImage( FAppStyle::GetBrush("NoBorder") )
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding( FMargin(0,3) )
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.FillWidth(1.0f)
			[
				// LEFT
				SAssignNew(LeftNodeBox, SVerticalBox)
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Center)
			.Padding(10.0f, 5.0f)
			[
				// ALIAS NAME
				SAssignNew(AliasName, STextBlock)
				.Text(this, &SDialogueGraphNode_Alias::GetAliasName)
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			[
				// RIGHT
				SAssignNew(RightNodeBox, SVerticalBox)
			]
		];
}
