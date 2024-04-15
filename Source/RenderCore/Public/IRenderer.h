#pragma once

#include "Containers/String.h"
#include "Template/Factory.h"


class RENDERCOREMODULEAPI IRenderer
{
public:
	IRenderer() {}
	~IRenderer() {}

	virtual void Init() = 0;
	virtual void EndPlay() = 0;
	virtual void Render(class World*) = 0;

	virtual unsigned int GetWidth() = 0;
	virtual unsigned int GetHeight() = 0;
private:

};



class RENDERCOREMODULEAPI RendererFactory : public Factory<IRenderer, String> {};