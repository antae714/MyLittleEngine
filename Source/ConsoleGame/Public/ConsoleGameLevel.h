#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Level.h"

class CONSOLEGAMEMODULEAPI ConsoleGameLevel : public Level
{
	GENERATED_BODY(ConsoleGameLevel, Level)
public:
	// Begin Level Implement
	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	// ~End Level Implement
};

