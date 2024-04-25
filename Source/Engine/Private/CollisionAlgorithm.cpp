#include "CollisionAlgorithm.h"
#include "Math/Rect.h"
#include "Math/Circle.h"
#include <algorithm>

bool CollisonAlgoritm::checkBoxBoxIntersection(const Rect& rect1, const Rect& rect2)
{
	bool isIntersects1 = rect1.Min.x < rect2.Max.x;
	bool isIntersects2 = rect1.Max.x > rect2.Min.x;

	bool isIntersects3 = rect1.Min.y < rect2.Max.y;
	bool isIntersects4 = rect1.Min.y < rect2.Max.y;

	return isIntersects1 && isIntersects2 && isIntersects3 && isIntersects4;
}

bool CollisonAlgoritm::checkBoxCircleIntersection(const Rect& rect, const Circle& circle)
{
	float closeX = std::clamp(circle.Center.x, rect.Min.x, rect.Max.x);
	float closeY = std::clamp(circle.Center.y, rect.Min.y, rect.Max.y);

	Vector closePoint = Vector(closeX, closeY);

	bool isIntersects = (circle.Center - closePoint).LengthSquared() <= powf(circle.Radius, 2.0f);
	return isIntersects;
}

bool CollisonAlgoritm::checkCircleCircleIntersection(const Circle& circle1, const Circle& circle2)
{
	float lengthSquared = (circle1.Center - circle2.Center).LengthSquared();

	bool isIntersects = lengthSquared <= powf(circle1.Radius + circle2.Radius, 2.0f);
	return isIntersects;
}
