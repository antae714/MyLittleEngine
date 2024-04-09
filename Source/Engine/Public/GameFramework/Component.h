#pragma once

class Actor;

class ENGINEMODULEAPI Component
{
public:
	Component();
	virtual ~Component();

public:
	virtual void BeginPlay() {}
	virtual void Update(float deltaTime) {}
	virtual void EndPlay() {}

	template <class T>
	T* GetOwner() { return dynamic_cast<T*>(owner); };
	Actor* GetOwner() { return owner; };
	void SetOwner(Actor* _owner) { owner = _owner; };


protected:
	class Actor* owner;
};

