// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNode.h"
#include "DialogueNodeData.h"
#include "DialogueGraphNode_Alias.generated.h"

USTRUCT()
struct MONOLITHDIALOGUESYSTEMEDITOR_API FAliasCounterTicket
{
	GENERATED_BODY()
	
	FAliasCounterTicket()
	{}
	
	FAliasCounterTicket(FString InAlias)
		: Alias(InAlias)
	{}
	
	FString Alias;
};

USTRUCT()
struct MONOLITHDIALOGUESYSTEMEDITOR_API FAliasCounter
{
	GENERATED_BODY()
	
	TMap<FString, int> Observers;

	void GetSubjects(TArray<FString>& InSubjects) const
	{
		Observers.GetKeys(InSubjects);
	}

	FAliasCounterTicket Subscribe(FString InObserver)
	{
		if (Observers.Find(InObserver))
		{
			Observers[InObserver]++;
		}
		else
		{
			Observers.Add(InObserver, 1);
		}
		return FAliasCounterTicket(InObserver);
	}
	
	void Unsubscribe(FAliasCounterTicket& InTicket)
	{
		FString Alias = InTicket.Alias;
		if (Observers.Find(Alias))
		{
			Observers[Alias]--;
			if (Observers[Alias] == 0)
			{
				Observers.Remove(Alias);
			}
		}
	}

};

UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueNodeData_Alias : public UDialogueNodeData
{
	GENERATED_BODY()

public:
	FText GetAliasName() const { return AliasName; }
	
	UPROPERTY(EditAnywhere)
	FText AliasName = FText::FromString("Placeholder");

	UPROPERTY()
	FAliasCounterTicket Ticket;
};
/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Alias : public UDialogueGraphNode
{
	GENERATED_BODY()

public:
	UDialogueGraphNode_Alias();
protected:

public: // UEdGraphNode Interface
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Black); }
	virtual bool CanUserDeleteNode() const override { return true; }
};

UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Alias_In : public UDialogueGraphNode_Alias
{
	GENERATED_BODY()

public: // UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override { return FText::FromString("Alias In"); }
	virtual void AllocateDefaultPins() override;
	
};

UCLASS()
class MONOLITHDIALOGUESYSTEMEDITOR_API UDialogueGraphNode_Alias_Out : public UDialogueGraphNode_Alias
{
	GENERATED_BODY()

public:
	virtual void InitializeNodeData() override;
	
public: // UEdGraphNode Interface
	virtual FText GetNodeTitle(ENodeTitleType::Type titalType) const override { return FText::FromString("Alias Out"); }
	virtual void AllocateDefaultPins() override;
	
};
