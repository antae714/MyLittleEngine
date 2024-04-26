#pragma once

#include "Math/Rect.h"
#include "Math/Circle.h"
#include "Math/Vector.h"
#include "Containers/DynamicArray.h"

namespace ECollisonShape { enum Type; }
class CollisonShape;

struct HitResult
{
	bool isHit;
	class Actor* hitActor;
	Vector hitPosition;
};


struct ENGINEMODULEAPI CollisonAlgorithm
{
	static bool Sweep(
		class World* world,
		HitResult& outResult,
		const Vector& start, 
		const Vector& end,
		CollisonShape shape,
		const DynamicArray<class Actor*>& ignoreActors
	);
	
	static bool checkLineLineIntersection(const CollisonShape& shape1, const CollisonShape& shape2);
	
	static bool checkBoxBoxIntersection(const CollisonShape& shape1, const CollisonShape& shape2);
	static bool checkBoxCircleIntersection(const CollisonShape& shape1, const CollisonShape& shape2);
	static bool checkCircleCircleIntersection(const CollisonShape& shape1, const CollisonShape& shape2);
};

