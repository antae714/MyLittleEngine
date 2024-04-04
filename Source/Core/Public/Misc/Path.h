#pragma once

#include "Containers/String.h"

class COREMODULEAPI Path
{
public:
	static WString getLaunchDir();
	static WString getConfigDir();
};

