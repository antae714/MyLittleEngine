#pragma once

#include "Math/Rect.h"
#include "Math/Circle.h"
#include "Math/Vector.h"
#include "Containers/DynamicArray.h"

namespace ECollisonShape { enum Type; }
namespace ECollisionChannel { enum Type; }
class CollisonShape;

struct HitResult
{
	bool isHit;
	class Actor* hitActor;
	Vector hitPosition;
	Vector hitNormal;
};


struct ENGINEMODULEAPI CollisonAlgorithm
{
	/**
	 * @brief 도형을 스윕하여 충돌 결과를 알아냅니다.
	 * @param outResult 알아낼 충돌 결과
	 * @param world 충돌처리할 월드
	 * @param start 시작지점
	 * @param end 끝지점
	 * @param shape 도형
	 * @param ignoreActors 무시할 액터들
	 * @param collisionChannel 충돌체크할 채널
	 * @return 충돌 여부
	 */
	static bool Sweep(
		HitResult& outResult,
		class World* world,
		const Vector& start,
		const Vector& end,
		CollisonShape shape,
		const DynamicArray<class Actor*>& ignoreActors,
		ECollisionChannel::Type collisionChannel,
		struct CollisionReactionArray collisionReactionArray
	);

	static bool Overlap(
		HitResult& outResult,
		class World* world,
		const Vector& point,
		CollisonShape shape,
		const DynamicArray<class Actor*>& ignoreActors
	);

	static bool checkLineLineIntersection(const CollisonShape& shape1, const CollisonShape& shape2);

	static float SweepBoxBox(const CollisonShape& shape1, const CollisonShape& shape2, const Vector& velocity, Vector& normal);
	static bool checkBoxBoxIntersection(const CollisonShape& shape1, const CollisonShape& shape2);
	static bool checkBoxCircleIntersection(const CollisonShape& shape1, const CollisonShape& shape2);
	static bool checkCircleCircleIntersection(const CollisonShape& shape1, const CollisonShape& shape2);
};

