#pragma once

#include "GameFramework/Component.h"

namespace ECollisonType
{
	enum
	{
		Box,
		Sphere,

		MAX
	};
}

class ENGINEMODULEAPI CollisionComponent : public Component
{
public:
	virtual int GetECollisonType() = 0;

	void HandleCollision(CollisionComponent* other);
	void ProcessCollision(CollisionComponent* other);
	bool CheckIntersects(CollisionComponent* other);

	






private:
	static bool checkBoxBoxIntersection(CollisionComponent* first, CollisionComponent* second);
	static bool checkBoxCircleIntersection(CollisionComponent* first, CollisionComponent* second);
	static bool checkCircleCircleIntersection(CollisionComponent* first, CollisionComponent* second);

	using CollisonIntersects = bool (*)(CollisionComponent*, CollisionComponent*);
	static CollisonIntersects InterSectsArray[ECollisonType::MAX][ECollisonType::MAX];
};
