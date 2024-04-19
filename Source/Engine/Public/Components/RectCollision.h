#pragma once

#include "Components/Collision.h"
#include "Math/Rect.h"

class ENGINEMODULEAPI RectCollision : public Collision
{
	friend class Collision;
public:
	RectCollision(const Rect& rect) : box(rect) {}

	virtual int GetECollisonType() override { return ECollisonType::Box; }

private:
	Rect box;
};