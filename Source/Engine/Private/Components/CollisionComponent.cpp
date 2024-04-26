#include "Components/CollisionComponent.h"
#include "Math/Rect.h"
#include "Math/Circle.h"
#include <algorithm>
#include "Components/RectCollisionComponent.h"
#include "Components/CircleCollisionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/World.h"
#include "Physics/CollisionAlgorithm.h"




void CollisionComponent::HandleSweepCollision(CollisionComponent* other, Vector startPosition, Vector endPosition)
{
	//if (CheckIntersects(other, endPosition - startPosition, other->owner->GetPosition()))
	//{
	//	ProcessCollision(other);
	//}
}

void CollisionComponent::ProcessCollision(CollisionComponent* other)
{


}

