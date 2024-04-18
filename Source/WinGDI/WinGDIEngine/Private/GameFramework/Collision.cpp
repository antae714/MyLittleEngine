#include "GameFramework/Collision.h"
#include "Rect.h"
#include "Circle.h"
#include <algorithm>
#include "GameFramework/BoxCollision.h"
#include "GameFramework/SphereCollision.h"


Collision::CollisonIntersects Collision::InterSectsArray[ECollisonType::MAX][ECollisonType::MAX] =
{
	{&checkBoxBoxIntersection, &checkBoxCircleIntersection},
	{&checkBoxCircleIntersection, &checkCircleCircleIntersection}
};



void Collision::HandleCollision(Collision* other)
{
	if (CheckIntersects(other))
	{
		ProcessCollision(other);
	}
}

void Collision::ProcessCollision(Collision* other)
{
}

bool Collision::CheckIntersects(Collision* other)
{
	CollisonIntersects IntersectsFunction = InterSectsArray[GetECollisonType()][other->GetECollisonType()];
	
	return IntersectsFunction(this, other);
}

bool Collision::checkBoxBoxIntersection(Collision* first, Collision* second)
{
	BoxCollision* fistCollision = dynamic_cast<BoxCollision*>(first);
	BoxCollision* secondCollision = dynamic_cast<BoxCollision*>(second);

	if (!(fistCollision && secondCollision)) throw std::exception();
	
	const Rect& rect1 = fistCollision->box;
	const Rect& rect2 = secondCollision->box;

	bool isIntersects1 = rect1.Min.x < rect2.Max.x;
	bool isIntersects2 = rect1.Max.x > rect2.Min.x;

	bool isIntersects3 = rect1.Min.y < rect2.Max.y;
	bool isIntersects4 = rect1.Min.y < rect2.Max.y;

	return isIntersects1 && isIntersects2 && isIntersects3 && isIntersects4;
}

bool Collision::checkBoxCircleIntersection(Collision* first, Collision* second)
{
	BoxCollision* fistCollision = dynamic_cast<BoxCollision*>(first);
	SphereCollision* secondCollision = dynamic_cast<SphereCollision*>(second);

	if (!(fistCollision && secondCollision))
	{
		fistCollision = dynamic_cast<BoxCollision*>(second);
		secondCollision = dynamic_cast<SphereCollision*>(first);

		if (!(fistCollision && secondCollision)) throw std::exception();
	}

	const Rect& rect = fistCollision->box;
	const Circle& circle = secondCollision->sphare;
	
	float closeX = std::clamp(circle.Center.x, rect.Min.x, rect.Max.x);
	float closeY = std::clamp(circle.Center.y, rect.Min.y, rect.Max.y);

	Vector closePoint = Vector(closeX, closeY);

	bool isIntersects = (circle.Center - closePoint).LengthSquared() <= powf(circle.Radius, 2.0f);
	return isIntersects;
}

bool Collision::checkCircleCircleIntersection(Collision* first, Collision* second)
{
	SphereCollision* fistCollision = dynamic_cast<SphereCollision*>(first);
	SphereCollision* secondCollision = dynamic_cast<SphereCollision*>(second);

	if (!(fistCollision && secondCollision)) throw std::exception();

	const Circle& circle1 = fistCollision->sphare;
	const Circle& circle2 = secondCollision->sphare;

	float lengthSquared = (circle1.Center - circle2.Center).LengthSquared();
	
	bool isIntersects = lengthSquared <= powf(circle1.Radius + circle2.Radius, 2.0f);
	return isIntersects;
}
