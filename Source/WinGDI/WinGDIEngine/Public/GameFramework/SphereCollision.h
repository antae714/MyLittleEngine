#pragma once

#include "Collision.h"
#include "Circle.h"

class WINGDIENGINEMODULEAPI SphereCollision : public Collision
{
	friend class Collision;
public:
	SphereCollision(const Circle& circle) : sphare(circle) {}

	virtual int GetECollisonType() override { return ECollisonType::Sphere; }

private:
	Circle sphare;
};
