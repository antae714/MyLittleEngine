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

class ENGINEMODULEAPI Collision : public Component
{
public:
	virtual int GetECollisonType() = 0;

	void HandleCollision(Collision* other);
	void ProcessCollision(Collision* other);
	bool CheckIntersects(Collision* other);

	






private:
	static bool checkBoxBoxIntersection(Collision* first, Collision* second);
	static bool checkBoxCircleIntersection(Collision* first, Collision* second);
	static bool checkCircleCircleIntersection(Collision* first, Collision* second);

	using CollisonIntersects = bool (*)(Collision*, Collision*);
	static CollisonIntersects InterSectsArray[ECollisonType::MAX][ECollisonType::MAX];
};
