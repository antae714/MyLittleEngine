#pragma once

#include "Containers/String.h"
#include "Containers/DynamicArray.h"

class ENGINEMODULEAPI Actor
{
public:
	Actor();
	virtual ~Actor();

public:	
	virtual void BeginPlay();
	virtual void Update(float deltaTime);
	virtual void EndPlay();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

protected:
	DynamicArray<class Component*> components;
	String name;
};