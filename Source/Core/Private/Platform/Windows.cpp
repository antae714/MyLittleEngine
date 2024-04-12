#include "Platform/Windows.h"

WindowApplication::WindowApplication(HINSTANCE _hInstance) : hInstance(_hInstance)
{
}

void WindowApplication::Resize(unsigned int width, unsigned int height)
{
}

void WindowApplication::AddOnResized(unsigned int width, unsigned int height)
{
}

void WindowApplication::RemoveOnResized(unsigned int width, unsigned int height)
{
}
