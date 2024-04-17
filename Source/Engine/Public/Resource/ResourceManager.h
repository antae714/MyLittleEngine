#pragma once

#include <type_traits>
#include "Containers/DynamicArray.h"
#include "Resource.h"


template<class ResourceLoader>
class ResourceManager
{
private:
	ResourceManager() = default;
public:
	static_assert(std::is_base_of_v<IResourceLoader, ResourceLoader>);

	struct ResourceContext
	{
		IResource* resource;
		int refenceCounter;
	};

	static ResourceManager* GetSingletonInstance()
	{
		static ResourceManager resourceManager;
		return resourceManager;
	}

	[[nodiscard]]
	IResource* GetResource(_In_ void* loadKey);
	void ReturnResource(IResource* resource);

private:
	DynamicArray<ResourceContext> resourceArray;
	ResourceLoader resourceLoader;
};

template<class ResourceLoader>
inline IResource* ResourceManager<ResourceLoader>::GetResource(_In_ void* loadKey)
{
	auto iter = resourceArray.Find([loadKey](ResourceContext& element) { return element.resource->CheckLoadKey(loadKey); });
	if (!iter)
	{
		iter = &resourceArray.Add();
		iter->resource = resourceLoader.Load(loadKey);
		iter->refenceCounter = 1;
	}
	else
	{
		iter->refenceCounter++;
	}

	return iter->resource;
}

template<class ResourceLoader>
inline void ResourceManager<ResourceLoader>::ReturnResource(IResource* resource)
{
	auto iter = resourceArray.Find([resource](ResourceContext& element) { return element.resource->CheckLoadKey(resource->GetLoadKey()); });
	if (!iter) throw std::exception();

	if (--iter->refenceCounter <= 0)
	{
		resourceLoader.UnLoad(iter->resource);
		resourceArray.Remove(iter);
	}
}
