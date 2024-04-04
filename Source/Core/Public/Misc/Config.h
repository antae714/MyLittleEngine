#pragma once

#include "Containers/String.h"
#include "Containers/DynamicArray.h"
#include "Misc/Path.h"



struct IniSettingBase
{
	String ini;
	String section;
	String key;
};

template <class T>
struct IniSetting : public IniSettingBase
{
	T value;
};

class COREMODULEAPI Config
{
private:
	Config() = default;
	static Config* GetConfig()
	{
		static Config config;
		return &config;
	}

public:
	template <class T>
	static bool GetValue(IniSetting<T>* iniSetting);
	template <class T>
	static void SetValue(IniSetting<T>* iniSetting);

private:
	template <class T>
	bool LoadConfig(IniSetting<T>* iniSetting);
	template <class T>
	bool FindValue(IniSetting<T>* iniSetting);

private:
	// 해쉬?
	DynamicArray<IniSettingBase*> parameterArray;

};

template<class T>
inline bool Config::GetValue(IniSetting<T>* iniSetting)
{
	bool isSecess = GetConfig()->FindValue<T>(iniSetting);
	if (!isSecess)
	{
		return GetConfig()->LoadConfig<T>(iniSetting);
	}
}

template<class T>
inline void Config::SetValue(IniSetting<T>* iniSetting)
{
	IniSetting<T>* deepCopyIniSetting = new IniSetting<T>(*(IniSetting<T>*)iniSetting);
	GetConfig()->parameterArray.Add(deepCopyIniSetting);

	//직력화 구현후 구현
}

template<class T>
inline bool Config::LoadConfig(IniSetting<T>* iniSetting)
{
	//직력화 구현후 구현
	Path::getConfigDir();
	return false;
}

template<class T>
inline bool Config::FindValue(IniSetting<T>* iniSetting)
{
	IniSettingBase** iter = GetConfig()->parameterArray.Find(
		[iniSetting](IniSettingBase*& element)
		{
			bool isIniSame = iniSetting->ini == element->ini;
			bool isSectionSame = iniSetting->section == element->section;
			bool isKeySame = iniSetting->key == element->key;

			return isIniSame && isSectionSame && isKeySame;
		}
	);
	if (!iter) return false;

	IniSetting<T>* findSetting = dynamic_cast<IniSetting<T>*>(*iter);

	if (!findSetting) return false;

	iniSetting->value = findSetting->value;

	return true;
}



