#include "Misc/Path.h"

WString Path::getLaunchDir()
{
	wchar_t path[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, path, MAX_PATH);
	int length = wcslen(path);
	for (int i = length - 1; i >= 0; i--)
	{
		if (path[i] == '\\')
		{
			path[i] = '\0';
			break;
		}
	}


    return WString(path);
}

WString Path::getConfigDir()
{
	return getLaunchDir() + WString(L"\\Config\\");
}
