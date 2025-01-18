// Fill out your copyright notice in the Description page of Project Settings.


#include "SDialogueGraphNode.h"

#include "DialogueGraphNode_Dialogue.h"
#include "DialogueNodeData_Dialogue.h"
#include "..\Public\DialogueGraphNode_Base.h"

void SDialogueGraphNode::Construct(const FArguments& InArgs, UDialogueGraphNode_Base* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

FText SDialogueGraphNode::GetDialogueText() const
{
	UDialogueGraphNode_Dialogue* DialogueNode = Cast<UDialogueGraphNode_Dialogue>(GraphNode);
	check(DialogueNode)

	UDialogueNodeData_Dialogue* NodeData = Cast<UDialogueNodeData_Dialogue>(DialogueNode->GetDialogueNodeData());
	return NodeData->DialogueText;
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
				SNew(SBorder)
				.BorderBackgroundColor(FSlateColor(FLinearColor::Gray))
				.Padding(10.0f)
				.Content()
				[
					SAssignNew(DialogueText, STextBlock)
					.MinDesiredWidth(260.0f)
					.Text(this, &SDialogueGraphNode::GetDialogueText)
					.WrapTextAt(250.0f)
				]
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
