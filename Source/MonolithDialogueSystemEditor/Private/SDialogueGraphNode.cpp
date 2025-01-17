﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "SDialogueGraphNode.h"

#include "..\Public\DialogueGraphNode_Base.h"

void SDialogueGraphNode::Construct(const FArguments& InArgs, UDialogueGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

FText SDialogueGraphNode::GetDialogueText() const
{
	// UDialogueGraphNode_Alias* AliasNode = Cast<UDialogueGraphNode_Alias>(GraphNode);
	// check(AliasNode);
	//
	// UDialogueNodeData_Alias* NodeData = Cast<UDialogueNodeData_Alias>(AliasNode->GetDialogueNodeData());
	// return NodeData->AliasName;

	return FText::FromString("");
}

void SDialogueGraphNode::UpdateGraphNode()
{
	SGraphNode::UpdateGraphNode();
}

TSharedRef<SWidget> SDialogueGraphNode::CreateNodeContentArea()
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
				// DIALOGUE TEXT
				SAssignNew(DialogueText, STextBlock)
				.Text(this, &SDialogueGraphNode::GetDialogueText)
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
