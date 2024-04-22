#include "Containers/String.h"

#include <utility>
#include <cstring>
#include <stdlib.h>
#include <strsafe.h>
#include <exception>

using namespace std;    


template class StringBase<char>;
template class StringBase<wchar_t>;


template<class T>
inline StringBase<T>::StringBase() : string{ nullptr }, length(0)
{
}

template<class T>
StringBase<T>::StringBase(const StringBase<T>& other) : StringBase<T>((const T*)other.string)
{

}

template<class T>
StringBase<T>::StringBase(StringBase<T>&& other) : StringBase<T>()
{
    string = other.string;
    length = other.length;

    other.string = nullptr;
    other.length = 0;
}

template<>
inline String::StringBase(const char* _string) : String()
{
    SecureMemory(strlen(_string));
    ::strcpy_s(string, length + 1, _string);
}

template<>
inline WString::StringBase(const wchar_t* _string) : WString()
{
    SecureMemory(lstrlenW(_string));
    StringCchCopyW(string, length + 1, _string);
}

//template<>
//template<>
//inline String::StringBase(const WString& _string) : String()
//{
//    size_t convertedNum;
//    SecureMemory(_string.length);
//
//    ::wcstombs_s(&convertedNum, string, length, _string.string, length);
//}
//
//template<>
//template<>
//inline WString::StringBase(const String& _string) : WString()
//{
//    size_t convertedNum;
//    SecureMemory(_string.length);
//
//    ::mbstowcs_s(&convertedNum, string, length, _string.string, _string.length);
//}



template<class T>
StringBase<T>::~StringBase()
{
    if (string)
    {
        free(string);
    }
}

template<class T>
bool StringBase<T>::IsEmpty() const
{
    return string[0] == '\0';
}

template<class T>
size_t StringBase<T>::Length() const
{
    return length;
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

template<class T>
void StringBase<T>::operator=(const StringBase<T>& other)
{
    SecureMemory(other.length);

    if constexpr (sizeof(T) == 1)
    {
        ::strcpy_s(string, length + 1, other.string);
    }
    else if constexpr(sizeof(T) == 2)
    {
        ::StringCchCopyW(string, length + 1, other.string);
    }

}

template<class T>
void StringBase<T>::SecureMemory(int _length)
{
    length = _length;

    if (length == 0)
    {
        if (string)
        {
            free(string);
        }
        return;
    }


    if (!string)
    {
        string = (T*)malloc((length + 1) * sizeof(T) );
        string[0] = '\0';
    }
    else
    {
        T* backup = (T*)realloc(string, (length + 1) * sizeof(T));
        if (!backup)
        {
            backup = (T*)malloc(length * sizeof(T));
            if (backup == nullptr) throw std::bad_alloc();

            memcpy(backup, string, length);
            free(string);
        }

        string = backup;
    }
}

template<>
void String::Concat(String& dest, const String& source)
{
    dest.SecureMemory(dest.length + source.length);

    ::strcat_s(dest.string, dest.length, source.string);
}

template<>
void WString::Concat(WString& dest, const WString& source)
{
    dest.SecureMemory(dest.length + source.length);

    ::lstrcatW(dest.string, source.string);
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


