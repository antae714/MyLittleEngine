#pragma once

#include "Collision.h"
#include "Rect.h"

class WINGDIENGINEMODULEAPI BoxCollision : public Collision
{
	friend class Collision;
public:
	BoxCollision(const Rect& rect) : box(rect) {}

	virtual int GetECollisonType() override { return ECollisonType::Box; }

private:
	Rect box;
};