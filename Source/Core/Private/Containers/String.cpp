#include "Containers/String.h"

#include <utility>
#include <cstring>
#include <stdlib.h>

using namespace std;    


template class StringBase<char>;
template class StringBase<wchar_t>;

template<class T>
inline StringBase<T>::StringBase() : string{0,}
{
}

template<>
inline String::StringBase(const char* _string) : String()
{
    if (_string)
    {
        ::strcpy_s(string, _string);
    }
}

template<>
inline WString::StringBase(const wchar_t* _string) : WString()
{
    if (_string)
    {
        ::lstrcpyW(string, _string);
    }
}

template<>
template<>
inline String::StringBase(const WString& _string) : String()
{
    size_t length;
    ::wcstombs_s(&length, string, _string.string, 256);
}

template<>
template<>
inline WString::StringBase(const String& _string) : WString()
{
    size_t length;
    ::mbstowcs_s(&length, string, _string.string, 256);
}
template<class T>
bool StringBase<T>::IsEmpty() const
{
    return string[0] == '\0';
}

template<>
size_t String::Length() const
{
    return strlen(string);
}

template<>
size_t WString::Length() const
{
    return lstrlenW(string);
}

template<class T>
size_t StringBase<T>::FindFirstDifference(const StringBase<T>& other) const
{
    size_t length = (std::max)(Length(), other.Length());
    for (size_t i = 0; i < length; i++)
    {
        if (string[i] != other.string[i])
        {
            return i;
        }
    }

    return length;
}

template<>
void String::Concat(String& dest, const String& source)
{
    ::strcat_s(dest.string, dest.string);
}

template<>
void WString::Concat(WString& dest, const WString& source)
{
    ::lstrcat(dest.string, dest.string);
}


template <>
inline bool String::Compare(const String& first, const String& second)
{
    return 0 == ::strcmp(first.string, second.string);
}

template<>
inline bool WString::Compare(const WString& first, const WString& second)
{
    return 0 == ::lstrcmpW(first.string, second.string);
}


