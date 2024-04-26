#pragma once

#include "GameFramework/Component.h"
#include "Math/Vector.h"
#include "Physics/CollisonShape.h"



class ENGINEMODULEAPI CollisionComponent : public Component
{
public:
	CollisonShape GetCollisonShape() { return shape; }
	void SetCollisonShape(CollisonShape _shape) { shape = _shape; }

public:
	void HandleSweepCollision(CollisionComponent* other, Vector startPosition, Vector endPosition);


private:
	void ProcessCollision(CollisionComponent* other);

	CollisonShape shape;



public:

};
