#pragma once

#include "Containers/String.h"
#include "Containers/DynamicArray.h"
#include "Math/Vector.h"

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
	T* GetComponent();
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	Vector GetPosition() { return position; }
protected:
	DynamicArray<Component*> components;
	String name;

	Vector position;
};

template<class T>
inline T* Actor::GetComponent()
{
	Component** findIter = components.Find([](Component*& element) { return !!dynamic_cast<T*>(element); });
	if (findIter)
	{
		return dynamic_cast<T*>(*findIter);
	}
	else
	{
		return nullptr;
	}

}