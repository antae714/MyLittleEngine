#include "Containers/String.h"

#include <utility>
#include <cstring>

using namespace std;    

bool String::Compare(const String& first, const String& second)
{
    return strcmp(first.str, second.str) == 0;
}