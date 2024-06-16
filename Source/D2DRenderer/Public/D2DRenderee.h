#pragma once

#include "IRenderer.h"

class D2DRENDERERMODULEAPI D2DRenderer : public IRenderer
{
	//Begine IRenderer Implementation
	virtual void Init() override;
	virtual void EndPlay() override;

	virtual void BeginRender() override;
	virtual void EndRender() override;

	virtual void RenderObject(IUnknown* renderResource, RenderData* renderData) override;
	virtual IUnknown* GetRenderResource(std::wstring name) override;

	virtual unsigned int GetWidth() override;
	virtual unsigned int GetHeight() override;

	virtual void ReSize(unsigned int newWidth, unsigned int newHeight) override;
	//~End IRenderer Implementation
};