#include "Containers/String.h"

#include <utility>
#include <cstring>

using namespace std;    

String::String() : String(nullptr)
{
}

String::String(const char* _string) : string{0,}
{
    if (_string)
    {
        strcpy_s(string, _string);
    }
}

bool String::Compare(const String& first, const String& second)
{
    return strcmp(first.string, second.string) == 0;
}