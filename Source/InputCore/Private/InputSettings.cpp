#include "InputSettings.h"

InputSettings::InputSettings()
{
	//����ȭ ������ ���� Config��� 

	inputArray.Add("UP", 0);
	inputArray.Add("Down", 0);
	inputArray.Add("Left", 0);
	inputArray.Add("Right", 0);
}


DynamicArray<InputData>& InputSettings::getInputData()
{
	return inputArray;
}
