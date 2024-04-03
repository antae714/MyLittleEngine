#pragma once

class ENGINEMODULEAPI Component
{
public:
	Component();
	virtual ~Component();

public:
	void BeginPlay() {}
	virtual void Update(float deltaTime) {}
	void EndPlay() {}
};

