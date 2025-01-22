// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueSystemComponent.generated.h"

class UDialogueRuntimeNode;
class UDialogueInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueEventSignature, UObject*, Payload);

USTRUCT(BlueprintType)
struct MONOLITHDIALOGUESYSTEMRUNTIME_API FDialogueText
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FText QueryText;

	UPROPERTY(BlueprintReadOnly)
	TArray<FText> ResponseTexts; 
	
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MONOLITHDIALOGUESYSTEMRUNTIME_API UDialogueSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDialogueSystemComponent();

	FDialogueText GetQueryAndResponse(UDialogueRuntimeNode* InRoot, int InIndex);

	UFUNCTION(BlueprintCallable)
	FDialogueText StartDialogue();

	UPROPERTY(BlueprintReadOnly)
	UDialogueRuntimeNode* CurrentNode = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDialogueInstance* Dialogue = nullptr;

	UPROPERTY(BlueprintAssignable)
	FDialogueEventSignature OnComponentInitialized;

	UPROPERTY(BlueprintAssignable)
	FDialogueEventSignature OnDialogueStart;

	UPROPERTY(BlueprintAssignable)
	FDialogueEventSignature OnDialogueEnd;

public: // UActorComponent Interface
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
