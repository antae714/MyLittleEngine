#include "Misc/Path.h"
#include <exception>


WString Path::GetLaunchDir()
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

WString Path::GetProjectDir()
{
	throw std::exception();

	static WString ProjectDir;
	if (ProjectDir.IsEmpty())
	{


	}


	return WString();
}

WString Path::GetConfigDir()
{
	return GetLaunchDir() + WString(L"\\Config\\");
}

WString Path::GetContentsDir()
{
	return GetLaunchDir() + WString(L"\\Contents\\");
}
