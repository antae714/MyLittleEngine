#pragma once

#include "Resource/Resource.h"
#include "Containers/String.h"

class BitMap : public IResource
{
public:
	BitMap(HBITMAP _bitmap) : bitmap(_bitmap), name() {}
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
	virtual IResource* Load(void* loadKey) override 
	{
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, *(WString*)loadKey, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BitMap* bitMap = new BitMap(hBitmap);
		bitMap->SetLoadKey(loadKey);
		return bitMap;
	}

	virtual void UnLoad(IResource* resource) override 
	{
		delete resource;
		DeleteObject(dynamic_cast<BitMap*>(resource)->GetBitmap());
	}
};

