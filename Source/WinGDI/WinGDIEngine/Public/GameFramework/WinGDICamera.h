#pragma once

#include "GameFramework/Camera.h"

class WINGDIENGINEMODULEAPI WinGDICamera : public Camera
{
	GENERATED_BODY(WinGDICamera, Camera)
public:
	// Begin Actor Implement
	virtual void BeginPlay() override;
	virtual void Update(float deltaTime) override;
	virtual void EndPlay() override;
	// ~End Actor Implement



private:
	class Character* playerCharacter;
};

