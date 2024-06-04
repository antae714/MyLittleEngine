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
	 * @brief ������ �����Ͽ� �浹 ����� �˾Ƴ��ϴ�.
	 * @param outResult �˾Ƴ� �浹 ���
	 * @param world �浹ó���� ����
	 * @param start ��������
	 * @param end ������
	 * @param shape ����
	 * @param ignoreActors ������ ���͵�
	 * @param collisionChannel �浹üũ�� ä��
	 * @return �浹 ����
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

