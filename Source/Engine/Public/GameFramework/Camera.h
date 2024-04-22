#pragma once

#include "GameFramework/Actor.h"

class ENGINEMODULEAPI Camera : public Actor
{

public:
	// Begin Actor Implement
	virtual void BeginPlay() override;
	virtual void Update(float deltaTime) override;
	virtual void EndPlay() override;
	// ~End Actor Implement


public:

	Vector ScreenToWorld();
	Vector WorldToScreen();

	Vector ViewPortToWorld();
	Vector WorldToViewPort();
	
	Vector ViewPortToScreen();
	Vector ScreenToViewPort();

private:
	unsigned int width;
	unsigned int height;

};

