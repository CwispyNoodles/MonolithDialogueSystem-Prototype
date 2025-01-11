// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class UDialogueGraphNode_Alias;
/**
 * 
 */
class MONOLITHDIALOGUESYSTEMEDITOR_API SDialogueGraphNode_Alias : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphNode_Alias) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UDialogueGraphNode_Alias* InNode);

private:
	FText GetAliasName() const;
	TSharedPtr<STextBlock> AliasName;

public: // SGraphNode Interface
	virtual void UpdateGraphNode() override;
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
};
