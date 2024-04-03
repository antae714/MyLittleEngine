#include "ConsoleGamePlayerCharacter.h"
#include "ConsoleMovementComponent.h"

void ConsoleGamePlayerCharacter::BeginPlay()
{
	Base::BeginPlay();
	AddComponent(new ConsoleMovementComponent());
}

void ConsoleGamePlayerCharacter::EndPlay()
{

	Base::EndPlay();
}
