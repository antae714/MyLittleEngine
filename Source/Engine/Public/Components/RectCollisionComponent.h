#pragma once

#include "Components/CollisionComponent.h"
#include "Math/Rect.h"
#include "Physics/CollisonShape.h"


//class ENGINEMODULEAPI RectCollisionComponent : public CollisionComponent
//{
//	friend class CollisionComponent;
//public:
//	RectCollisionComponent(const Rect& rect) : box(rect) {}
//
//	virtual int GetECollisonType() override { return ECollisonShape::Box; }
//	virtual void* GetCollison() override { return &box; }
//
//private:
//	Rect box;
//};