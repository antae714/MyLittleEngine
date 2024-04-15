#include "Application/Application.h"

void IApplication::SetSingletonInstance(IApplication* instance)
{
	if (singletonInstance && instance) throw std::exception("¾Û Áßº¹ »ý¼º");
	singletonInstance = instance;
}
