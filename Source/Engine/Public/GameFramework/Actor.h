#pragma once

#include "Containers/String.h"
#include "Containers/DynamicArray.h"
#include "Math/Vector.h"
#include <type_traits>
#include "Containers/Delegate.h"

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

	template<class T>
	T* AddComponent();

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	String GetName() { return name; }
	void SetName(String _name) { name = _name; }

	Vector GetPosition() { return position; }
	void SetPosition(Vector targetPosition);
	void MovePosition(Vector targetPosition);

	class World* GetWorld();

public:
	class Level* ownedLevel;

protected:

	DynamicArray<Component*> components;
	
	String name;

	Vector position;

	Delegate<struct HitResult> onCollision;
	//Delegate<> onTriger;
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

template<class T>
inline T* Actor::AddComponent()
{
	static_assert(std::is_base_of<Component, T>::value);
	T* component = new T();
	AddComponent(component);
	component->SetOwner(this);
	return component;
}