#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Level.h"

class WINGDIGAMEMODULEAPI WinGDIGameLevel : public Level
{
	GENERATED_BODY(WinGDIGameLevel, Level)
public:
	// Begin Level Implement
	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	// ~End Level Implement
};

