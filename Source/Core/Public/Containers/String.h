#pragma once

#ifdef StringImplement

class String
{
};

#else



class COREMODULEAPI String
{
public:
    static bool Compare(const String& first, const String& second);
    bool operator==(const String& other) const { return Compare(*this, other); }

private:
    char str[32];
    unsigned int strSize = 32;
};




#endif // StringImplement



