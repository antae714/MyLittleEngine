#include "Application/Application.h"

void IApplication::SetSingletonInstance(IApplication* instance)
{
	if (singletonInstance && instance) throw std::exception("�� �ߺ� ����");
	singletonInstance = instance;
}
