#pragma once

#include "Containers/String.h"
#include "Containers/DynamicArray.h"
#include "Template/Factory.h"
#include "EngineInput.h"



class INPUTCOREMODULEAPI IInputProcessor
{
public:
	virtual void ProcessInput() = 0;
	virtual DynamicArray<EngineInput>* getEngineInputArray() = 0;
};

class INPUTCOREMODULEAPI InputProcessorFactory : public Factory<IInputProcessor, String> { };

