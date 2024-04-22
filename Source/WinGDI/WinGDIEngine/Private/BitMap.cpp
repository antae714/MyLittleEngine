#include "BitMap.h"
#include "Misc/Path.h"


IResource* BitMapLoader::Load(void* loadKey)
{
	WString includePath = Path::GetContentsDir() + *(WString*)loadKey;

	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, includePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	BitMap* bitMap = new BitMap(hBitmap);
	bitMap->SetLoadKey(loadKey);
	return bitMap;
}

void BitMapLoader::UnLoad(IResource* resource)
{
	DeleteObject(dynamic_cast<BitMap*>(resource)->GetBitmap());
	delete resource;
}



