#ifdef TEST_APP
#include <gtest/gtest.h>

#include "../src/main.h"
#include <fstream>

TEST(TroubleWithFile, OpenFile)             //Try to open test file (../WS_file_test.pcap)
{
    std::ifstream in;
    in.open("../WS_file_test.pcap");
    ASSERT_EQ(1, in.is_open());
}


TEST(CheckFile, IsEmpty)                    //Check for test file open
{
    std::list<Package> packList;
    readPcapFile(packList);
    ASSERT_EQ(0, packList.empty());
}

TEST(MacToStrFunc, CorrResult)           //Check for MAC conversion from u_char array to string (00:00:00:00:00:00)
{
    const u_char macData[6] = {0, 0, 0, 0, 0, 0};
    std::string outStr;
    createMacString(macData, outStr);
    ASSERT_EQ("00:00:00:00:00:00", outStr);
}

TEST(ReadData, NumberOfPacs)                 //Check for read packs count(303)
{
    std::list<Package> packList;
    readPcapFile(packList);
    ASSERT_EQ(303, packList.size());
}

TEST(FindUnicMacsFunc, NumberOfUniqueMacs)  //Check for function that finds unique MAC addresses(2)
{
    std::list<Package> packList;
    std::list<UniqueMacStat> uniqueMacs;
    readPcapFile(packList);
    findUniqueMacs(packList, uniqueMacs);
    ASSERT_EQ(2, uniqueMacs.size());
}

TEST(CalcStatMacsFunc, CorrOuputValues)     //Check for function that calculates statistics
{
    std::list<Package> packList;
    std::list<UniqueMacStat> uniqueMacs;
    readPcapFile(packList);
    findUniqueMacs(packList, uniqueMacs);
    calcStatistics(packList, uniqueMacs);
    ASSERT_EQ(131, uniqueMacs.begin()->count);
    ASSERT_EQ(26670, uniqueMacs.begin()->size);
    ASSERT_EQ(172, std::next(uniqueMacs.begin())->count);
    ASSERT_EQ(115352, std::next(uniqueMacs.begin())->size);
}

TEST(PackageTest, OperatorIsEqTrue)     //Check for Package operator==
{
    Package packLeft, packRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 0};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 0};
    memcpy(packLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(packRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_EQ(packLeft, packRight);
}

TEST(PackageTest, OperatorIsEqFalse)     //Check for Package operator==
{
    Package packLeft, packRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 10};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 0};
    memcpy(packLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(packRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_FALSE(packLeft == packRight);
}

TEST(PackageTest, OperatorLessTrue)     //Check for Package operator<
{
    Package packLeft, packRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 0};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 10};
    memcpy(packLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(packRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_LT(packLeft, packRight);
}

TEST(PackageTest, OperatorLessFalseGr)     //Check for Package operator<
{
    Package packLeft, packRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 10};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 0};
    memcpy(packLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(packRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_FALSE(packLeft < packRight);
}

TEST(PackageTest, OperatorLessFalseEq)     //Check for Package operator<
{
    Package packLeft, packRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 0};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 0};
    memcpy(packLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(packRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_FALSE(packLeft < packRight);
}

TEST(PackageTest, DstMacToStr)     //Check for function dstMacToStr()
{
    Package pack;
    u_char dstMac[7] = {0, 0, 0, 0, 0, 0};
    memcpy(pack.dstMac, dstMac, sizeof(u_char)*6);
    ASSERT_EQ("00:00:00:00:00:00", pack.dstMacToStr());
}

TEST(UniqueMacStat, OperatorIsEqTrue)     //Check for UniqueMacStat operator==
{
    UniqueMacStat statLeft, statRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 0};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 0};
    memcpy(statLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(statRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_EQ(statLeft, statRight);
}

TEST(UniqueMacStat, OperatorIsEqFalse)     //Check for UniqueMacSta operator==
{
    UniqueMacStat statLeft, statRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 10};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 0};
    memcpy(statLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(statRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_FALSE(statLeft == statRight);
}

TEST(UniqueMacStat, OperatorLessTrue)     //Check for UniqueMacSta operator<
{
    UniqueMacStat statLeft, statRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 0};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 10};
    memcpy(statLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(statRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_LT(statLeft, statRight);
}

TEST(UniqueMacStat, OperatorLessFalseGr)     //Check for UniqueMacSta operator<
{
    UniqueMacStat statLeft, statRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 10};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 0};
    memcpy(statLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(statRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_FALSE(statLeft < statRight);
}

TEST(UniqueMacStat, OperatorLessFalseEq)     //Check for UniqueMacSta operator<
{
    UniqueMacStat statLeft, statRight;
    u_char dstMacLeft[7] = {0, 0, 0, 0, 0, 0};
    u_char dstMacRight[7] = {0, 0, 0, 0, 0, 0};
    memcpy(statLeft.dstMac, dstMacLeft, sizeof(u_char)*6);
    memcpy(statRight.dstMac, dstMacRight, sizeof(u_char)*6);
    ASSERT_FALSE(statLeft < statRight);
}

TEST(UniqueMacStat, DstMacToString)     //Check for function dstMacToString()
{
    UniqueMacStat stat;
    u_char dstMac[7] = {0, 0, 0, 0, 0, 0};
    memcpy(stat.dstMac, dstMac, sizeof(u_char)*6);
    ASSERT_EQ("00:00:00:00:00:00", stat.dstMacToString());
}

#endif
