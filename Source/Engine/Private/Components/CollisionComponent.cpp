#include "Components/CollisionComponent.h"
#include "Math/Rect.h"
#include "Math/Circle.h"
#include <algorithm>
#include "Components/RectCollisionComponent.h"
#include "Components/CircleCollisionComponent.h"


CollisionComponent::CollisonIntersects CollisionComponent::InterSectsArray[ECollisonType::MAX][ECollisonType::MAX] =
{
	{&checkBoxBoxIntersection, &checkBoxCircleIntersection},
	{&checkBoxCircleIntersection, &checkCircleCircleIntersection}
};



void CollisionComponent::HandleCollision(CollisionComponent* other)
{
	if (CheckIntersects(other))
	{
		ProcessCollision(other);
	}
}

void CollisionComponent::ProcessCollision(CollisionComponent* other)
{
}

bool CollisionComponent::CheckIntersects(CollisionComponent* other)
{
	CollisonIntersects IntersectsFunction = InterSectsArray[GetECollisonType()][other->GetECollisonType()];
	
	return IntersectsFunction(this, other);
}

bool CollisionComponent::checkBoxBoxIntersection(CollisionComponent* first, CollisionComponent* second)
{
	RectCollisionComponent* fistCollision = dynamic_cast<RectCollisionComponent*>(first);
	RectCollisionComponent* secondCollision = dynamic_cast<RectCollisionComponent*>(second);

	if (!(fistCollision && secondCollision)) throw std::exception();
	
	const Rect& rect1 = fistCollision->box;
	const Rect& rect2 = secondCollision->box;

	bool isIntersects1 = rect1.Min.x < rect2.Max.x;
	bool isIntersects2 = rect1.Max.x > rect2.Min.x;

	bool isIntersects3 = rect1.Min.y < rect2.Max.y;
	bool isIntersects4 = rect1.Min.y < rect2.Max.y;

	return isIntersects1 && isIntersects2 && isIntersects3 && isIntersects4;
}

bool CollisionComponent::checkBoxCircleIntersection(CollisionComponent* first, CollisionComponent* second)
{
	RectCollisionComponent* fistCollision = dynamic_cast<RectCollisionComponent*>(first);
	CircleCollisionComponent* secondCollision = dynamic_cast<CircleCollisionComponent*>(second);

	if (!(fistCollision && secondCollision))
	{
		fistCollision = dynamic_cast<RectCollisionComponent*>(second);
		secondCollision = dynamic_cast<CircleCollisionComponent*>(first);

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

bool CollisionComponent::checkCircleCircleIntersection(CollisionComponent* first, CollisionComponent* second)
{
	CircleCollisionComponent* fistCollision = dynamic_cast<CircleCollisionComponent*>(first);
	CircleCollisionComponent* secondCollision = dynamic_cast<CircleCollisionComponent*>(second);

	if (!(fistCollision && secondCollision)) throw std::exception();

	const Circle& circle1 = fistCollision->sphare;
	const Circle& circle2 = secondCollision->sphare;

	float lengthSquared = (circle1.Center - circle2.Center).LengthSquared();
	
	bool isIntersects = lengthSquared <= powf(circle1.Radius + circle2.Radius, 2.0f);
	return isIntersects;
}
