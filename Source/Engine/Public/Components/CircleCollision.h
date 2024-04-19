#pragma once

#include "Components/Collision.h"
#include "Math/Circle.h"

class ENGINEMODULEAPI CircleCollision : public Collision
{
	friend class Collision;
public:
	CircleCollision(const Circle& circle) : sphare(circle) {}

	virtual int GetECollisonType() override { return ECollisonType::Sphere; }

private:
	Circle sphare;
};
