#pragma once

#include "Containers/String.h"
#include "Containers/DynamicArray.h"

class Component;

class ENGINEMODULEAPI Actor
{
public:
	Actor();
	virtual ~Actor();

public:	
	virtual void BeginPlay();
	virtual void Update(float deltaTime);
	virtual void EndPlay();

	template<class T>
	Component* GetComponent();
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

protected:
	DynamicArray<Component*> components;
	String name;
};

template<class T>
inline Component* Actor::GetComponent()
{
	return *components.Find([](Component*& element) { return !!dynamic_cast<T*>(element); });

}