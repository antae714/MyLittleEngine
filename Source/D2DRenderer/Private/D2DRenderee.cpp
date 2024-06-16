#include "IRenderer.h"
#include "D2DRenderee.h"
#include <d2d1.h>

void D2DRenderer::Init()
{
}

void D2DRenderer::EndPlay()
{
}

void D2DRenderer::BeginRender()
{
}

void D2DRenderer::EndRender()
{
}

void D2DRenderer::RenderObject(IUnknown* renderResource, RenderData* renderData)
{
}

IUnknown* D2DRenderer::GetRenderResource(std::wstring name)
{
	return nullptr;
}

unsigned int D2DRenderer::GetWidth()
{
	return 0;
}

unsigned int D2DRenderer::GetHeight()
{
	return 0;
}

void D2DRenderer::ReSize(unsigned int newWidth, unsigned int newHeight)
{
}
