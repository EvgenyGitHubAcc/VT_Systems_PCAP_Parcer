#include "main.h"

int main(void)
{
#ifndef TEST_APP
    std::list<Package> packList;
    std::list<UniqueMacStat> uniqueMacs;
    readPcapFile(packList);
    findUniqueMacs(packList, uniqueMacs);
    calcStatistics(packList, uniqueMacs);
    printStat(uniqueMacs);
    return 0;
#else
    ::testing::InitGoogleTest();
      return RUN_ALL_TESTS();
#endif
}

void printStat(std::list<UniqueMacStat> &uniqueDstMac)
{
    std::cout << "Package statistics" << std::endl;
    for(std::list<UniqueMacStat>::iterator setIt = uniqueDstMac.begin(); setIt != uniqueDstMac.end(); ++setIt)
    {
        std::cout << "Destination MAC: " << setIt->dstMacToString() << ", Count: " << setIt->count << ", Total size(bytes): " << setIt->size << std::endl;
    }
}

void findUniqueMacs(std::list<Package> & packList, std::list<UniqueMacStat> & uniqueDstMac)
{
    std::set<UniqueMacStat> macStatSet;
    for(std::list<Package>::iterator it = packList.begin(); it != packList.end(); ++ it)
    {
        UniqueMacStat obj;
        memcpy(obj.dstMac, it->dstMac, 6);
        macStatSet.insert(obj);
    }
    uniqueDstMac = std::list<UniqueMacStat>(macStatSet.begin(), macStatSet.end());
}

void calcStatistics(std::list<Package> & packList, std::list<UniqueMacStat> & uniqueDstMac)
{
    for(std::list<UniqueMacStat>::iterator setIt = uniqueDstMac.begin(); setIt != uniqueDstMac.end(); ++setIt)
    {
        for(std::list<Package>::iterator it = packList.begin(); it != packList.end(); ++ it)
        {
            if(setIt->dstMacToString() == it->dstMacToStr())
            {
                setIt->size += it->packSize;
                ++(setIt->count);
            }
        }
    }
}

void createMacString(const u_char macData[], std::string & str)
{
    std::stringstream ss;
    char oldFill = ss.fill('0');
    ss << std::setw(2) << std::hex << static_cast<unsigned int>(macData[0]);
    for (u_int i = 1; i < 6; ++i)
    {
        ss << ':' << std::setw(2) << std::hex << static_cast<unsigned int>(macData[i]);
    }
    ss.fill(oldFill);
    str = ss.str();
}

void printPackages(std::list<Package> & packList)
{
    std::string str;
    for(std::list<Package>::iterator it = packList.begin(); it != packList.end(); ++it)
    {
        std::cout << it->dstMacToStr() << std::endl;
    }
}

void readPcapFile(std::list<Package> & packList)
{
    char errbuff[PCAP_ERRBUF_SIZE];
    pcap_t * pcap = nullptr;
#ifndef TEST
    pcap = pcap_open_offline("../WS_file.pcap", errbuff);

#else
    pcap = pcap_open_offline("../WS_file_test.pcap", errbuff);

#endif

#ifndef TEST_APP

    if(pcap == nullptr)
    {
        std::cout << "Error open pcap file" << std::endl;
        exit(0);
    }

    std::cout << "Pcap file opened" << std::endl;

#endif

    struct pcap_pkthdr *header;
    const u_char *data;

    while (int returnValue = pcap_next_ex(pcap, &header, &data) >= 0)
    {
        Package pack;
        pack.packSize = header->len;
        for (u_int i = 0; i < header->caplen; i++)
        {
            if(i < 6)
            {
                pack.dstMac[i] = data[i];
            }
            if(i <= 6 && i < 12 )
            {
                pack.srcMac[i] = data[i];
            }
        }
        packList.push_back(pack);
    }
}
