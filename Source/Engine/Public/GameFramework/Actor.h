#pragma once

#include "Containers/String.h"

class ENGINEMODULEAPI Actor
{
public:
	Actor();
	~Actor();

public:
	virtual void Update(float TickTime) {}

private:
	String name;
};