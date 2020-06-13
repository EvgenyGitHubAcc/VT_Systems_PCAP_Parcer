#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <pcap.h>
#include <list>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <set>
#include "package.h"
#include "uniquemacstat.h"

struct UniqueMacStat;
struct Package;

void readPcapFile(std::list<Package> & packList);
void printPackages(std::list<Package> & packList);
void createMacString(const u_char macData[], std::string & str);
void findUniqueMacs(std::list<Package> & packList, std::list<UniqueMacStat> &uniqueDstMac);
void calcStatistics(std::list<Package> & packList, std::list<UniqueMacStat> &uniqueDstMac);
void printStat(std::list<UniqueMacStat> &uniqueDstMac);

#endif // MAIN_H
