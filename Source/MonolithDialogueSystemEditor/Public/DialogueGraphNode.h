// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueGraphNode.generated.h"

class UDialogueNodeData;
/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	void SetPosition(FVector2D InPos);
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	virtual void OnPropertiesChanged() {}
	void SetDialogueNodeData(UDialogueNodeData* InNodeData) { DialogueNodeData = InNodeData; }
	UDialogueNodeData* GetDialogueNodeData() { return DialogueNodeData; }

	UPROPERTY()
	FText NodeTitle = FText::FromString("Placeholder");

protected:
	UPROPERTY()
	UDialogueNodeData* DialogueNodeData = nullptr;
	
};
