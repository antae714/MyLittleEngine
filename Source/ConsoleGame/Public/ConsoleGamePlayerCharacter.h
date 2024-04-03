#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

class CONSOLEGAMEMODULEAPI ConsoleGamePlayerCharacter : public Character
{
	GENERATED_BODY(ConsoleGamePlayerCharacter, Character)
public:
	// Begin Actor Implement
	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	// ~End Actor Implement
};

