#pragma once

#include "ConsoleConfig.h"

namespace ConsoleRendererExample
{
	RENDERERMODULEAPI void ScreenInit();
	RENDERERMODULEAPI void ScreenRelease();

	RENDERERMODULEAPI void ScreenFlipping();
	RENDERERMODULEAPI void ScreenClear();	

    RENDERERMODULEAPI bool ScreenSetChar(int x, int y, char ch, WORD attr);
	RENDERERMODULEAPI bool ScreenSetString(int x, int y, const char* pStr, WORD attr);
	RENDERERMODULEAPI bool ScreenSetAttr(WORD attr);

	RENDERERMODULEAPI int ScreenWidth();
	RENDERERMODULEAPI int ScreenHeight();
};


