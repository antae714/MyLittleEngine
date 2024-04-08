#pragma once

#include "GameFramework/Component.h"

struct CONSOLEENGINEMODULEAPI RenderData
{
	int row;
	int colum;

	WORD attribute;
};


class CONSOLEENGINEMODULEAPI ConsoleRenderComponent : public Component
{
public:
	RenderData renderData;
};

