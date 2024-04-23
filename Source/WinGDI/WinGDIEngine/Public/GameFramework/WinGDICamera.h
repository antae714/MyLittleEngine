#pragma once

#include "GameFramework/Camera.h"

class WINGDIENGINEMODULEAPI WinGDICamera : public Camera
{
	GENERATED_BODY(WinGDICamera, Camera)
	// Begin Actor Implement
	virtual void BeginPlay() override;
	virtual void EndPlay() override;
	// ~End Actor Implement

};

