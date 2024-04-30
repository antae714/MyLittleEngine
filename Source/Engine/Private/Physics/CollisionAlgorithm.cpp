#include "Physics/CollisionAlgorithm.h"
#include "Math/Rect.h"
#include "Math/Circle.h"
#include <algorithm>
#include <limits>
#include "GameFramework/World.h"
#include "GameFramework/Actor.h"
#include "Components/CollisionComponent.h"
#include "Physics/CollisonShape.h"

class CollisonIntersectsFunction
{
public:
	using CollisonIntersects = bool (*)(const CollisonShape&, const CollisonShape&);

public:
	static bool Excute(const CollisonShape& first, const CollisonShape& second);
	

private:
	inline static CollisonIntersects InterSectsArray[ECollisonShape::MAX][ECollisonShape::MAX] =
	{
		{ &CollisonAlgorithm::checkLineLineIntersection, nullptr, nullptr},
		{nullptr, &CollisonAlgorithm::checkBoxBoxIntersection, &CollisonAlgorithm::checkBoxCircleIntersection},
		{nullptr, &CollisonAlgorithm::checkBoxCircleIntersection, &CollisonAlgorithm::checkCircleCircleIntersection}
	};
};

bool CollisonIntersectsFunction::Excute(const CollisonShape& first, const CollisonShape& second)
{
	CollisonIntersects find = InterSectsArray[first.GetCollisonShape()][second.GetCollisonShape()];

	return find(first, second);
}

bool CollisonAlgorithm::Sweep (
	class World* world,
	HitResult& outResult,
	const Vector& start,
	const Vector& end,
	CollisonShape shape,
	const DynamicArray<Actor*>& ignoreActors
)
{	
	outResult = HitResult();
	for (auto& actorList : world->GetAllActor())
	{
		for (auto& actor : *actorList)
		{
			if (ignoreActors.Contains(actor)) continue;

			CollisionComponent* collisionComponent = actor->GetComponent<CollisionComponent>();
			if (!collisionComponent) continue;	
			//	bool isHit = CollisonIntersectsFunction::Excute(
			//	shape + end,
			//	collisionComponent->GetCollisonShape() + actor->GetPosition()
			//);

			//if (!isHit) continue;

			float SweppTime = SweepBoxBox(shape + start, 
										  collisionComponent->GetCollisonShape() + actor->GetPosition(),
										  end - start,
										  outResult.hitNormal);
			if(SweppTime > 1.0f || SweppTime < 0.0f)  continue;
			

			outResult.hitPosition = start + (end - start) * SweppTime;

			outResult.hitActor = actor;
			outResult.isHit = true;


			return true;
		}
	}

	return outResult.isHit;
}

bool CollisonAlgorithm::checkLineLineIntersection(const CollisonShape& shape1, const CollisonShape& shape2)
{
	Line line1 = shape1.GetLine();
	Line line2 = shape2.GetLine();

	float line1ToLine2start = (line1.end - line1.start).CrossProduct(line2.start - line1.start).z;
	float line1ToLine2end = (line1.end - line1.start).CrossProduct(line2.end - line1.start).z;
	float line1IntersectValue1 = line1ToLine2start * line1ToLine2end;
	bool isline1Intersect = line1IntersectValue1 <= 0;

	float line2ToLine1start = (line2.end - line2.start).CrossProduct(line1.start - line2.start).z;
	float line2ToLine1end = (line2.end - line2.start).CrossProduct(line1.end - line2.start).z;
	float line1IntersectValue2 = line2ToLine1start * line2ToLine1end;
	bool isline2Intersect = line1IntersectValue2 <= 0;

	//line1IntersectValue1 * line1IntersectValue2


	return isline1Intersect && isline2Intersect;
}

float CollisonAlgorithm::SweepBoxBox(const CollisonShape& shape1, const CollisonShape& shape2, const Vector& velocity, Vector& normal)
{
	//https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
	//참고 하였습니다.

	Rect rect1 = shape1.GetRect();
	Rect rect2 = shape2.GetRect();

	Vector CollideEnterPosition;
	Vector CollideExitPosition;
	Vector deltaEnter;
	Vector deltaExit;

	if (velocity.x > 0.0f)
	{
		CollideEnterPosition.x = rect2.Min.x - rect1.Max.x;
		CollideExitPosition.x = rect2.Max.x - rect1.Min.x;
	}
	else
	{
		CollideEnterPosition.x = rect2.Max.x - rect1.Min.x;
		CollideExitPosition.x = rect2.Min.x - rect1.Max.x;
	}
	if (velocity.y > 0.0f)
	{
		CollideEnterPosition.y = rect2.Min.y - rect1.Max.y;
		CollideExitPosition.y = rect2.Max.y - rect1.Min.y;
	}
	else
	{
		CollideEnterPosition.y = rect2.Max.y - rect1.Min.y;
		CollideExitPosition.y = rect2.Min.y - rect1.Max.y;
	}

	if (velocity.x == 0.0f) 
	{
		bool isIntersects = rect1.Min.x < rect2.Max.x && rect1.Max.x > rect2.Min.x;
		deltaEnter.x = std::numeric_limits<float>::infinity() * (isIntersects ? -1.0f : 1.0f);
		deltaExit.x = std::numeric_limits<float>::infinity() * (isIntersects ? 1.0f : -1.0f);
	}
	else
	{
		deltaEnter.x = CollideEnterPosition.x / velocity.x;
		deltaExit.x = CollideExitPosition.x / velocity.x;
	}
	if (velocity.y == 0.0f)
	{
		bool isIntersects = rect1.Min.y < rect2.Max.y && rect1.Max.y > rect2.Min.y;
		deltaEnter.y = std::numeric_limits<float>::infinity() * (isIntersects ? -1.0f : 1.0f);
		deltaExit.y = std::numeric_limits<float>::infinity() * (isIntersects ? 1.0f : -1.0f);
	}
	else
	{
		deltaEnter.y = CollideEnterPosition.y / velocity.y;
		deltaExit.y = CollideExitPosition.y / velocity.y;
	}

	float sweepEntreyTime = (std::max)(deltaEnter.x, deltaEnter.y);
	float sweepExitTime = (std::min)(deltaExit.x, deltaExit.y);



	bool isEnter = sweepEntreyTime < 1.0f && sweepEntreyTime > 0.0f 
					&& sweepExitTime > 0.0f;
	if (!isEnter)
	{
		return FLT_MAX;
	}


	if (deltaEnter.x < deltaEnter.y)
	{
		normal.y = CollideEnterPosition.y < 0 ? 1.0f : -1.0f;
	}
	else
	{
		normal.x = CollideEnterPosition.x > 0 ? 1.0f : -1.0f;
	}

	return sweepEntreyTime;
}

bool CollisonAlgorithm::checkBoxBoxIntersection(const CollisonShape& shape1, const CollisonShape& shape2)
{
	Rect rect1 = shape1.GetRect();
	Rect rect2 = shape2.GetRect();

	bool isIntersects1 = rect1.Min.x < rect2.Max.x;
	bool isIntersects2 = rect1.Max.x > rect2.Min.x;

	bool isIntersects3 = rect1.Min.y < rect2.Max.y;
	bool isIntersects4 = rect1.Min.y < rect2.Max.y;

	return isIntersects1 && isIntersects2 && isIntersects3 && isIntersects4;
}

bool CollisonAlgorithm::checkBoxCircleIntersection(const CollisonShape& shape1, const CollisonShape& shape2)
{
	Rect rect;
	Circle circle;

	if (shape1.GetCollisonShape() == ECollisonShape::Box)
	{
		rect = shape1.GetRect();
		circle = shape2.GetCircle();
	}
	else
	{
		rect = shape2.GetRect();
		circle = shape1.GetCircle();
	}

	float closeX = std::clamp(circle.Center.x, rect.Min.x, rect.Max.x);
	float closeY = std::clamp(circle.Center.y, rect.Min.y, rect.Max.y);

	Vector closePoint = Vector(closeX, closeY);

	bool isIntersects = (circle.Center - closePoint).LengthSquared() <= powf(circle.Radius, 2.0f);
	return isIntersects;
}

bool CollisonAlgorithm::checkCircleCircleIntersection(const CollisonShape& shape1, const CollisonShape& shape2)
{
	Circle circle1 = shape1.GetCircle();
	Circle circle2 = shape2.GetCircle();

	float lengthSquared = (circle1.Center - circle2.Center).LengthSquared();

	bool isIntersects = lengthSquared <= powf(circle1.Radius + circle2.Radius, 2.0f);
	return isIntersects;
}
