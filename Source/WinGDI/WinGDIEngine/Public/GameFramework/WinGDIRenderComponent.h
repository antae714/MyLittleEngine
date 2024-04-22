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

	HBITMAP GetHBITMAP() { return bitmap->GetBitmap(); }

	Rect GetRenderArea() { return renderArea; }

	void SetImageName(const WString& _imageName) { imageName = _imageName; }
	void SetRenderArea(Rect area) { renderArea = area; }

private:
	Rect renderArea;
	WString imageName;
	BitMap* bitmap;
};

