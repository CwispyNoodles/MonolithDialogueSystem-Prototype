// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class UDialogueGraphNode_Base;
/**
 * 
 */
class MONOLITHDIALOGUESYSTEMEDITOR_API SDialogueGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UDialogueGraphNode_Base* InNode);

	FText GetDialogueText() const;

	TSharedPtr<STextBlock> DialogueText;

public: // SGraphNode Interface
	virtual void UpdateGraphNode() override;
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
};
