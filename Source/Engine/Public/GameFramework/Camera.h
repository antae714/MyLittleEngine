#pragma once

#include "GameFramework/Actor.h"
#include "Math/ScreenSize.h"
#include "CoreMinimal.h"

class ENGINEMODULEAPI Camera : public Actor
{
	GENERATED_BODY(Camera, Actor)
public:
	Camera();

public:
	// Begin Actor Implement
	virtual void BeginPlay() override;
	virtual void Update(float deltaTime) override;
	virtual void EndPlay() override;
	// ~End Actor Implement


public:
	void SetRenderBoxExtents(Vector _renderBoxExtents);


	Vector ViewPortToWorld(Vector viewportPosition);
	Vector WorldToViewPort(Vector worldPosition);
	

private:
	Vector renderBoxExtents;

	Vector viewportSize;
	Vector viewportScale;
};

