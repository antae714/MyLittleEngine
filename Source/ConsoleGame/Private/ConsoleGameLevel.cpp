#include "ConsoleGameLevel.h"
#include "ConsoleGamePlayerCharacter.h"

void ConsoleGameLevel::BeginPlay()
{
	Base::BeginPlay();
	AddActor(new ConsoleGamePlayerCharacter());
}

void ConsoleGameLevel::EndPlay()
{
	Base::EndPlay();
}
