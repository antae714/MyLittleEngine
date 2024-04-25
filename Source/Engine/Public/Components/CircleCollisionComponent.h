#pragma once

#include "Components/CollisionComponent.h"
#include "Math/Circle.h"

class ENGINEMODULEAPI CircleCollisionComponent : public CollisionComponent
{
	friend class CollisionComponent;
public:
	CircleCollisionComponent(const Circle& circle) : sphare(circle) {}

	virtual int GetECollisonType() override { return ECollisonType::Sphere; }
	virtual void* GetCollison() override { return &sphare; }

private:
	Circle sphare;
};
