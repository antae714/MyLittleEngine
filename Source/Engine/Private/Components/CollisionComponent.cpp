#include "Components/CollisionComponent.h"
#include "Math/Rect.h"
#include "Math/Circle.h"
#include <algorithm>
#include "Components/RectCollisionComponent.h"
#include "Components/CircleCollisionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/World.h"
#include "CollisionAlgorithm.h"


CollisionComponent::CollisonIntersects CollisionComponent::InterSectsArray[ECollisonType::MAX][ECollisonType::MAX] =
{
	{&checkBoxBoxIntersection, &checkBoxCircleIntersection},
	{&checkBoxCircleIntersection, &checkCircleCircleIntersection}
};


void CollisionComponent::HandleSweepCollision(CollisionComponent* other, Vector startPosition, Vector endPosition)
{
	if (CheckIntersects(other, endPosition - startPosition, other->owner->GetPosition()))
	{
		ProcessCollision(other);
	}
}

void CollisionComponent::ProcessCollision(CollisionComponent* other)
{


}

bool CollisionComponent::CheckIntersects(CollisionComponent* other, Vector Position, Vector otherPosition)
{
	CollisonIntersects IntersectsFunction = InterSectsArray[GetECollisonType()][other->GetECollisonType()];
	
	return IntersectsFunction(this, other, Position, otherPosition);
}

bool CollisionComponent::checkBoxBoxIntersection(CollisionComponent* first, CollisionComponent* second, Vector firstPos, Vector secondPos)
{
	return CollisonAlgoritm::checkBoxBoxIntersection(
		*(Rect*)first->GetCollison() + firstPos, 
		*(Rect*)second->GetCollison() + secondPos
	);
}

bool CollisionComponent::checkBoxCircleIntersection(CollisionComponent* first, CollisionComponent* second, Vector firstPos, Vector secondPos)
{
	if (!dynamic_cast<RectCollisionComponent*>(first))
	{
		std::swap(first, second);
	}

	return CollisonAlgoritm::checkBoxCircleIntersection(
		*(Rect*)first->GetCollison() + firstPos,
		*(Circle*)second->GetCollison() + secondPos
	);

}

bool CollisionComponent::checkCircleCircleIntersection(CollisionComponent* first, CollisionComponent* second, Vector firstPos, Vector secondPos)
{
	return CollisonAlgoritm::checkCircleCircleIntersection(
		*(Circle*)second->GetCollison() + firstPos,
		*(Circle*)first->GetCollison() + secondPos
	);
}
