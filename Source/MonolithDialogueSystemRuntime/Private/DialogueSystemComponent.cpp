// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystemComponent.h"

#include "DialogueInstance.h"


// Sets default values for this component's properties
UDialogueSystemComponent::UDialogueSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

FDialogueHandle UDialogueSystemComponent::StartDialogue()
{
	// if (!WorkingDialogue)
	// {
	// 	WorkingDialogue = NewObject<UDialogueInstance>(this, Dialogue);
	// }
	//
	// return WorkingDialogue->GetFirstDialogueNode();

	return FDialogueHandle();
}


// Called when the game starts
void UDialogueSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDialogueSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

