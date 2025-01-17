// Fill out your copyright notice in the Description page of Project Settings.


#include "SDialogueGraphNode.h"

void SDialogueGraphNode::Construct(const FArguments& InArgs, UDialogueGraphNode* InNode)
{
}

void SDialogueGraphNode::UpdateGraphNode()
{
	SGraphNode::UpdateGraphNode();
}

TSharedRef<SWidget> SDialogueGraphNode::CreateNodeContentArea()
{
	return SGraphNode::CreateNodeContentArea();
}
