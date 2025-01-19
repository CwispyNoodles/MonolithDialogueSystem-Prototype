// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\SDialogueGraphNode_Query.h"

#include "DialogueGraphNode_Dialogue.h"
#include "DialogueNodeData_Dialogue.h"
#include "..\Public\DialogueGraphNode_Base.h"

void SDialogueGraphNode_Query::Construct(const FArguments& InArgs, UDialogueGraphNode_Base* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

FText SDialogueGraphNode_Query::GetDialogueText() const
{
	UDialogueGraphNode_Dialogue* DialogueNode = Cast<UDialogueGraphNode_Dialogue>(GraphNode);
	check(DialogueNode)

	UDialogueNodeData_Query* NodeData = Cast<UDialogueNodeData_Query>(DialogueNode->GetDialogueNodeData());
	return NodeData->QueryText;
}

void SDialogueGraphNode_Query::UpdateGraphNode()
{
	SGraphNode::UpdateGraphNode();
}

TSharedRef<SWidget> SDialogueGraphNode_Query::CreateNodeContentArea()
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
					.Text(this, &SDialogueGraphNode_Query::GetDialogueText)
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
