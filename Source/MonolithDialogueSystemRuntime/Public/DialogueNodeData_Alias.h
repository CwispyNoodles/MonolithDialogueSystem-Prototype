// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeData.h"
#include "DialogueNodeData_Alias.generated.h"

USTRUCT()
struct MONOLITHDIALOGUESYSTEMRUNTIME_API FAliasCounterTicket
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
struct MONOLITHDIALOGUESYSTEMRUNTIME_API FAliasCounter
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

/**
 * 
 */
UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueNodeData_Alias_In : public UDialogueNodeData
{
	GENERATED_BODY()

public:
	FText GetAliasName() const { return AliasName; }
	
	UPROPERTY(EditAnywhere)
	FText AliasName = FText::FromString("Placeholder");

	UPROPERTY()
	FAliasCounterTicket Ticket;
};

UCLASS()
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueNodeData_Alias_Out : public UDialogueNodeData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FText AliasName;
};
