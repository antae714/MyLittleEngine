#pragma once

#include "ConsoleConfig.h"

namespace ConsoleRendererExample
{
	CONSOLERENDERERMODULEAPI void ScreenInit();
	CONSOLERENDERERMODULEAPI void ScreenRelease();

	CONSOLERENDERERMODULEAPI void ScreenFlipping();
	CONSOLERENDERERMODULEAPI void ScreenClear();

	CONSOLERENDERERMODULEAPI bool ScreenSetChar(int x, int y, char ch, WORD attr);
	CONSOLERENDERERMODULEAPI bool ScreenSetString(int x, int y, const char* pStr, WORD attr);
	CONSOLERENDERERMODULEAPI bool ScreenSetAttr(WORD attr);

	CONSOLERENDERERMODULEAPI int ScreenWidth();
	CONSOLERENDERERMODULEAPI int ScreenHeight();
};


