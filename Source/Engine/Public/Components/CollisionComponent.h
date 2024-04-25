#pragma once

#include "GameFramework/Component.h"
#include "Math/Vector.h"

struct ECollisonType
{
	enum
	{
		Box,
		Sphere,

		MAX
	};
};

class ENGINEMODULEAPI CollisionComponent : public Component
{
public:
	virtual int GetECollisonType() = 0;
	virtual void* GetCollison() = 0;

public:
	void HandleSweepCollision(CollisionComponent* other, Vector startPosition, Vector endPosition);
	bool CheckIntersects(CollisionComponent* other, Vector Position, Vector otherPosition);

private:
	void ProcessCollision(CollisionComponent* other);





private:
	static bool checkBoxBoxIntersection(CollisionComponent* first, CollisionComponent* second, Vector firstPos, Vector secondPos);
	static bool checkBoxCircleIntersection(CollisionComponent* first, CollisionComponent* second, Vector firstPos, Vector secondPos);
	static bool checkCircleCircleIntersection(CollisionComponent* first, CollisionComponent* second, Vector firstPos, Vector secondPos);

	using CollisonIntersects = bool (*)(CollisionComponent*, CollisionComponent*, Vector, Vector);
	static CollisonIntersects InterSectsArray[ECollisonType::MAX][ECollisonType::MAX];
};
