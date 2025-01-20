// Fill out your copyright notice in the Description page of Project Settings.


#include "SDialogueGraphPin_Response_Output.h"

#include "DialogueGraphNode_Response.h"
#include "DialogueNodeData_Dialogue.h"


void SDialogueGraphPin_Response_Output::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InPin);
	FullPinHorizontalRowWidget.Pin()
	->InsertSlot(0)
	[
		SNew(SBorder)
		.BorderBackgroundColor(FSlateColor(FLinearColor::Gray))
		.Padding(10.0f)
		.Content()
		[
			SAssignNew(ResponseText, STextBlock)
			.MinDesiredWidth(260.0f)
			.WrapTextAt(250.0f)
			.Text(this, &SDialogueGraphPin_Response_Output::GetResponseText)
		]
	];
	
}

FText SDialogueGraphPin_Response_Output::GetResponseText() const
{
	UEdGraphPin* ParentPin = GetPinObj();
	if (UDialogueGraphNode_Response* ResponseNode = Cast<UDialogueGraphNode_Response>(ParentPin->GetOwningNode()))
	{
		int Index = ResponseNode->Pins.Find(ParentPin);
		if (Index != INDEX_NONE)
		{
			UDialogueNodeData_Response* NodeData = Cast<UDialogueNodeData_Response>(ResponseNode->GetDialogueNodeData());
			if (NodeData->ResponseTexts.IsValidIndex(Index-1))
			{
				return NodeData->ResponseTexts[Index-1];
			}
		}
	}
	return FText();
}
