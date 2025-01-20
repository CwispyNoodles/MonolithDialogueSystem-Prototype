// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueGraphNode_Base.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDialogueNodeEventSignature, UEdGraphNode*)

class UDialogueNodeData_Base;
/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Base : public UEdGraphNode
{
	GENERATED_BODY()

public:
	void SetPosition(FVector2D InPos);
	virtual void OnPropertiesChanged() { GetGraph()->NotifyNodeChanged(this); }
	void SetDialogueNodeData(UDialogueNodeData_Base* InNodeData) { DialogueNodeData = InNodeData; }
	UDialogueNodeData_Base* GetDialogueNodeData() const { return DialogueNodeData; }
	virtual void InitializeNodeData();
	UEdGraphPin* GetDefaultInputPin() { return DefaultInputPin; }
protected:
	UPROPERTY()
	TSubclassOf<UDialogueNodeData_Base> NodeDataClass;
	
	UPROPERTY()
	UDialogueNodeData_Base* DialogueNodeData = nullptr;
	
	UEdGraphPin* DefaultInputPin = nullptr;

public: // UEdGraphNode Interface
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
	
};
