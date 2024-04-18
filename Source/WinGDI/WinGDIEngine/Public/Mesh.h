#pragma once

#include "Rect.h"
#include "Circle.h"

class Mesh
{
public:
	virtual ~Mesh() {}
};

class RectMesh : public Mesh
{
public:
	virtual ~RectMesh() {}
	Rect rect;
};

class CircleMesh : public Mesh
{
public:
	virtual ~CircleMesh() {}
	Circle circle;
};
