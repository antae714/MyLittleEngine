#pragma once

#include "Resource/Resource.h"
#include "Containers/String.h"

class BitMap : public IResource
{
public:
	virtual ~BitMap() = default;
	
public:
	virtual bool CheckLoadKey(void* loadKey) override 
	{
		return name == *(String*)loadKey;
	}

	virtual void SetLoadKey(void* loadKey) override
	{
		name = *(String*)loadKey;
	}

	virtual void* GetLoadKey() override
	{
		return &name;
	}

public:
	String name;
};

class BitMapLoader : public IResourceLoader
{
public:
	virtual ~BitMapLoader() = default;

public:
	[[nodiscard]]
	virtual IResource* Load(void* loadKey) override 
	{
		BitMap* bitMap = new BitMap();
		bitMap->SetLoadKey(loadKey);
		return bitMap;
	}

	virtual void UnLoad(IResource* resource) override 
	{
		delete resource;
	}
};

