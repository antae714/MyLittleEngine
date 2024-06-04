#pragma once

#include "GameFramework/Component.h"
#include "Math/Vector.h"
#include "Physics/CollisonShape.h"
#include "Containers/Delegate.h"


namespace ECollisionChannel
{
	enum Type
	{
		Default,
		MAX
	};
}

enum class ECollisionReaction
{
	Ignore,
	Overlap,
	Block
};

struct CollisionReactionArray
{
	ECollisionReaction reactions[ECollisionChannel::MAX];
};



class ENGINEMODULEAPI CollisionComponent : public Component
{
public:
	CollisonShape shape;

	ECollisionChannel::Type collisionType;
	CollisionReactionArray collisionReactionArray;

public:
	Delegate<struct HitResult> onCollision;


};

