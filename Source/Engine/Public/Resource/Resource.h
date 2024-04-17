#pragma once


class IResource
{
public:
	virtual ~IResource() = default;

public:
	virtual bool CheckLoadKey(void* loadKey) = 0;

	virtual void SetLoadKey(void* loadKey) = 0;
	virtual void* GetLoadKey() = 0;
};

class IResourceLoader
{
public:
	virtual ~IResourceLoader() = default;

public:
	virtual IResource* Load(void* loadKey) = 0;
	virtual void UnLoad(IResource* resource) = 0;
};

