#pragma once

#include "Containers/String.h"

class COREMODULEAPI Path
{
public:
	static WString GetLaunchDir();
	static WString GetProjectDir();
	static WString GetConfigDir();
	static WString GetContentsDir();
};

