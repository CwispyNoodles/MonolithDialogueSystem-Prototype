// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueNode.h"
#include "ToolMenu.h"

void UDialogueNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Dialogue Node Actions")));

	UDialogueNode* Node = (UDialogueNode*)this;
	Section.AddMenuEntry
	(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add Pin")),
		FText::FromString(TEXT("Creates a new pin")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda(
			[Node] ()
			{
				Node->CreateCustomPin(
					EGPD_Output,
					TEXT("AnotherOutput"));
				Node->GetGraph()->NotifyGraphChanged();
				Node->GetGraph()->Modify();
			}))
	);

	Section.AddMenuEntry
	(
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete Pin")),
		FText::FromString(TEXT("Deletes last pin")),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda(
			[Node] ()
			{
				UEdGraphPin* Pin = Node->GetPinAt(Node->Pins.Num() - 1);
				if (Pin->Direction != EGPD_Input)
				{
					Node->RemovePin(Pin);
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
