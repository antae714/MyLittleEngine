#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Component.h"
#include "Math/Vector.h"


class CONSOLEENGINEMODULEAPI ConsolePathFinder : public Component
{
	GENERATED_BODY(ConsolePathFinder, Component)

public:
	virtual void Update(float deltaTime);

	void CalculatePath(Vector pos, Vector targetPos);
	DynamicArray<Vector>& GetPath() { return Path ; }

	class ConsoleWorldSetting* worldSettings;
private:
	DynamicArray<Vector> Path;
	Vector CalculatedPos;
};

