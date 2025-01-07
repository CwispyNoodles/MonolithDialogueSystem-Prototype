// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueNode.h"

#include "DialogueNodeInfo.h"
#include "ToolMenu.h"

void UDialogueNode::SyncPinsWithResponses()
{
	// Sync the pins on the node with the dialogue Responses
	// We're going to assume the first pin is always the input pin
	UDialogueNodeInfo* DialogueNodeInfo = GetNodeInfo();
	int NumGraphNodePins = Pins.Num() - 1;
	int NumInfoPins = DialogueNodeInfo->DialogueResponses.Num();

	while (NumGraphNodePins > NumInfoPins) {
		RemovePinAt(NumGraphNodePins - 1, EEdGraphPinDirection::EGPD_Output);
		NumGraphNodePins--;
	}
	while (NumInfoPins > NumGraphNodePins) {
		CreateCustomPin(
			EEdGraphPinDirection::EGPD_Output,
			FName(DialogueNodeInfo->DialogueResponses[NumGraphNodePins].ToString())
		);
		NumGraphNodePins++;
	}

	int index = 1;
	for (const FText& option : DialogueNodeInfo->DialogueResponses) {
		GetPinAt(index)->PinName = FName(option.ToString());
		index++;
	}
}

FText UDialogueNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	UDialogueNodeInfo* nodeInfo = Cast<UDialogueNodeInfo>(NodeInfo);
	if (nodeInfo->Title.IsEmpty()) {
		FString dialogTextStr = nodeInfo->DialogueText.ToString();
		if (dialogTextStr.Len() > 15) {
			dialogTextStr = dialogTextStr.Left(15) + TEXT("...");
		}
		return FText::FromString(dialogTextStr);
	}
	return nodeInfo->Title;
}

void UDialogueNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));

	UDialogueNode* Node = (UDialogueNode*)this;
	Section.AddMenuEntry
	(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add Response")),
		FText::FromString(TEXT("Creates a new pin")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda(
			[Node] ()
			{
				Node->GetNodeInfo()->DialogueResponses.Add(FText::FromString(TEXT("Response")));
				Node->SyncPinsWithResponses();
				
				Node->GetGraph()->NotifyGraphChanged();
				Node->GetGraph()->Modify();
			}))
	);

	Section.AddMenuEntry
	(
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete Response")),
		FText::FromString(TEXT("Deletes last pin")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda(
			[Node] ()
			{
				UEdGraphPin* Pin = Node->GetPinAt(Node->Pins.Num() - 1);
				if (Pin->Direction != EGPD_Input)
				{
					UDialogueNodeInfo* Info = Node->GetNodeInfo();
					Info->DialogueResponses.RemoveAt(Info->DialogueResponses.Num() - 1);
					Node->SyncPinsWithResponses();
					
					Node->GetGraph()->NotifyGraphChanged();
					Node->GetGraph()->Modify();
				}
			}))
	);

	Section.AddMenuEntry
	(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes Node")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda(
			[Node] ()
			{
				Node->GetGraph()->RemoveNode(Node);
			}))
	);
}

UEdGraphPin* UDialogueNode::CreateCustomPin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = (Direction == EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	FName Subcategory = TEXT("DialoguePin");

	UEdGraphPin* Pin = CreatePin
	(
		Direction,
		Category,
		Name
	);

	Pin->PinType.PinSubCategory = Subcategory;

	return Pin;
}
