#pragma once
#include "Module/ModuleBase.h"

class InputCoreModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};