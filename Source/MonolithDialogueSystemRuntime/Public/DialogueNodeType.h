// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DialogueNodeType.generated.h"

/**
 * 
 */
UENUM()
enum class EDialogueNodeType {
	None,
	Root,
	Query,
	Response,
	AliasIn,
	AliasOut
};