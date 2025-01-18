// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphSchema.generated.h"

USTRUCT()
struct MONOLITHDIALOGUESYSTEMEDITOR_API FDialogueGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

public:
	FDialogueGraphSchemaAction()
		: FEdGraphSchemaAction()
	{
	}
	
	FDialogueGraphSchemaAction(FText InNodeCategory, FText InMenuDesc, FText InToolTip, FText InKeywords = FText::GetEmpty(), int32 InGrouping = 0)
		: FEdGraphSchemaAction(
			MoveTemp(InNodeCategory),
			MoveTemp(InMenuDesc),
			MoveTemp(InToolTip),
			MoveTemp(InGrouping),
			MoveTemp(InKeywords))
	{
	}
};

USTRUCT()
struct MONOLITHDIALOGUESYSTEMEDITOR_API FDialogueGraphSchemaAction_NewNode : public FDialogueGraphSchemaAction
{
	GENERATED_BODY()

public:
	FDialogueGraphSchemaAction_NewNode() 
		: FDialogueGraphSchemaAction()
	{}

	FDialogueGraphSchemaAction_NewNode(UClass* InClassTemplate, FText InNodeCategory, FText InMenuDesc, FText InToolTip, FText InKeywords = FText::GetEmpty(), int32 InGrouping = 0)
		: FDialogueGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InKeywords, InGrouping), ClassTemplate(InClassTemplate)
	{}

	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	UEdGraphNode* CreateNode(UEdGraph* InParentGraph, FVector2D InLocation);
protected:
	UClass* ClassTemplate = nullptr;
};

USTRUCT()
struct MONOLITHDIALOGUESYSTEMEDITOR_API FDialogueGraphSchemaAction_NewNode_AliasOut : public FDialogueGraphSchemaAction_NewNode
{
	GENERATED_BODY()

public:
	FDialogueGraphSchemaAction_NewNode_AliasOut() 
		: FDialogueGraphSchemaAction_NewNode()
	{}

	FDialogueGraphSchemaAction_NewNode_AliasOut(UClass* InClassTemplate, FText InAliasName, FText InNodeCategory, FText InMenuDesc, FText InToolTip, FText InKeywords = FText::GetEmpty(), int32 InGrouping = 0)
		: FDialogueGraphSchemaAction_NewNode(InClassTemplate, InNodeCategory, InMenuDesc, InToolTip, InKeywords, InGrouping), AliasName(InAliasName)
	{}

	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;

protected:
	 FText AliasName;
};
/**
 * 
 */
UCLASS(MinimalAPI)
class UDialogueGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public: // UEdGraphSchema Interface
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	// virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
};
