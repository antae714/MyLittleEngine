
#include "InputCoreModule.h"
#include "IInputProcessor.h"
#include "WindowInputProcessor.h"

//IMPLEMENT_MODULE(InputCore)
DEFINE_MODULE(InputCore);

void InputCoreModule::StartUpModule()
{
	InputProcessorFactory::Add<WindowInputProcessor>("window");
}

void InputCoreModule::ShotDownModule()
{
	InputProcessorFactory::Remove("window");
}
