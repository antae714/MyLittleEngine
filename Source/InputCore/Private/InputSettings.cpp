#include "InputSettings.h"

InputSettings::InputSettings()
{
	//����ȭ ������ ���� Config��� 

	inputActionArray.Add("UP", 0);
	inputActionArray.Add("Down", 0);
	inputActionArray.Add("Left", 0);
	inputActionArray.Add("Right", 0);

	inputAxisArray.Add("Left/Right", 0.f);
}
