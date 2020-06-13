#include "package.h"

bool Package::operator==(const Package &obj) const
{
    unsigned long long thisMac = 0, objMac = 0;
    thisMac = dstMac[0];
    thisMac <<= 8;
    objMac = obj.dstMac[0];
    objMac <<= 8;
    for(u_int i = 0; i < 6; ++i)
    {
        thisMac += dstMac[i];
        thisMac <<= 8;
        objMac += obj.dstMac[i];
        objMac <<= 8;
    }
    return thisMac == objMac;
}

bool Package::operator<(const Package &obj) const
{
    unsigned long long thisMac = 0, objMac = 0;
    thisMac = dstMac[0];
    thisMac <<= 8;
    objMac = obj.dstMac[0];
    objMac <<= 8;
    for(u_int i = 0; i < 6; ++i)
    {
        thisMac += dstMac[i];
        thisMac <<= 8;
        objMac += obj.dstMac[i];
        objMac <<= 8;
    }
    return thisMac < objMac;
}

std::string Package::dstMacToStr() const
{
    std::string str;
    createMacString(dstMac, str);
    return str;
}
