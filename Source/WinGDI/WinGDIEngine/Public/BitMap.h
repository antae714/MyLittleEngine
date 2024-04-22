#pragma once

#include "Resource/Resource.h"
#include "Containers/String.h"

class BitMap : public IResource
{
public:
	BitMap(HBITMAP _bitmap) : bitmap(_bitmap), name() {}
	virtual ~BitMap() = default;
	
public:
	virtual bool CheckLoadKey(void* loadKey) override { return name == *(String*)loadKey; }

	virtual void SetLoadKey(void* loadKey) override { name = *(String*)loadKey; }

	virtual void* GetLoadKey() override { return &name; }
	
	HBITMAP GetBitmap() { return bitmap; }

private:
	String name;
	HBITMAP bitmap;
};

class BitMapLoader : public IResourceLoader
{
public:
	virtual ~BitMapLoader() = default;

public:
	[[nodiscard]]
	virtual IResource* Load(void* loadKey) override;
	
	virtual void UnLoad(IResource* resource) override;
	
};

