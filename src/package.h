#ifndef PACKAGE_H
#define PACKAGE_H

#include "main.h"

struct Package
{
    u_char dstMac[7] = {0};
    u_char srcMac[7] = {0};
    u_int packSize = 0;
    bool operator== (const Package& obj) const;
    bool operator< (const Package& obj) const;
    std::string dstMacToStr() const;
};

#endif // PACKAGE_H
