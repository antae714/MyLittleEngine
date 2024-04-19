#pragma once

#include <type_traits>


template <class T>
class COREMODULEAPI StringBase
{
    friend StringBase<char>;
    friend StringBase<wchar_t>;

public:
    StringBase();
    StringBase(const T* _string);
    template <class T2>
    StringBase(const T2& _string);

public:
    bool IsEmpty() const;
    size_t Length() const;
    size_t FindFirstDifference(const StringBase<T>& other) const;

public:
    static void Concat(StringBase<T>& dest, const StringBase<T>& source);
    static bool Compare(const StringBase<T>& first, const StringBase<T>& second);
    
    bool operator==(const StringBase<T>& other) const { return Compare(*this, other); }
    StringBase<T>& operator+=(const StringBase<T>& other) { Concat(*this, other); return *this; }
    StringBase<T> operator+(const StringBase<T>& other) const { StringBase<T> dest; Concat(dest, *this); Concat(dest, other); return std::move(dest); }
    
    operator T* ()
    {
        return string;
    }
private:
    T string[32];
};


using String = StringBase<char>;
using WString = StringBase<wchar_t>;

