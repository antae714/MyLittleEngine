#pragma once

#include "Components/CollisionComponent.h"
#include "Math/Rect.h"

class ENGINEMODULEAPI RectCollisionComponent : public CollisionComponent
{
	friend class CollisionComponent;
public:
	RectCollisionComponent(const Rect& rect) : box(rect) {}

	virtual int GetECollisonType() override { return ECollisonType::Box; }

private:
	Rect box;
};