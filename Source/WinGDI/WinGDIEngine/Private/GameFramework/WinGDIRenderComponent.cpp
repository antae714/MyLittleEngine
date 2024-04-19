#include "GameFramework/WinGDIRenderComponent.h"
#include "Resource/ResourceManager.h"

void WinGDIRenderComponent::BeginPlay()
{
	bitmap = (BitMap*)ResourceManager<BitMapLoader>::GetSingletonInstance()->GetResource(&imageName);
}

void WinGDIRenderComponent::EndPlay()
{
	ResourceManager<BitMapLoader>::GetSingletonInstance()->ReturnResource(bitmap);
}
