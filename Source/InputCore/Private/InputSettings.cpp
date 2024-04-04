#include "InputSettings.h"

InputSettings::InputSettings()
{
	//직렬화 구현시 변경 Config사용 

	inputArray.Add("UP", 0);
	inputArray.Add("Down", 0);
	inputArray.Add("Left", 0);
	inputArray.Add("Right", 0);
}


DynamicArray<InputData>& InputSettings::getInputData()
{
	return inputArray;
}
