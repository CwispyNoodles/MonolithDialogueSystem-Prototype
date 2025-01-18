// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNode_Base.h"
#include "DialogueGraphNode_Alias.generated.h"



/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Alias : public UDialogueGraphNode_Base
{
	GENERATED_BODY()

public: // UEdGraphNode Interface
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Black); }
	virtual bool CanUserDeleteNode() const override { return true; }
};

UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Alias_In : public UDialogueGraphNode_Alias
{
	GENERATED_BODY()

public:
	UDialogueGraphNode_Alias_In();

public: // UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override { return FText::FromString("Alias In"); }
	virtual void AllocateDefaultPins() override;
	
};

UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Alias_Out : public UDialogueGraphNode_Alias
{
	GENERATED_BODY()

public:
	UDialogueGraphNode_Alias_Out();
	
public: // UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override { return FText::FromString("Alias Out"); }
	virtual void AllocateDefaultPins() override;
	
};
