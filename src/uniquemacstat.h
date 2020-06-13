#ifndef UNIQUEMACSTAT_H
#define UNIQUEMACSTAT_H

#include "main.h"

struct UniqueMacStat
{
    u_char dstMac[7] = {0};
    u_int count = 0;
    u_int size = 0;
    std::string dstMacToString() const;
    bool operator<(const UniqueMacStat& obj) const;
    bool operator==(const UniqueMacStat& obj) const;
};

#endif // UNIQUEMACSTAT_H
