#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Component.h"
#include "Math/Rect.h"
#include "BitMap.h"

class WINGDIENGINEMODULEAPI WinGDIRenderComponent : public Component
{
	GENERATED_BODY(WinGDIRenderComponent, Component)
public:
	// Begin Component Implement
	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	// ~End Component Implement


private:
	Rect renderArea;
	String imageName;
	BitMap* bitmap;
};

