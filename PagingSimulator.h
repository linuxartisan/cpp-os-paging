#ifndef PAGINGSIMULATOR_H
#define PAGINGSIMULATOR_H

#include <string>
#include <fstream>
#include <vector>
#include "Process.h"


/**
 * The simulator that handles the aging algorithm logic.
 */
class PagingSimulator
{
private:
    std::ifstream fs;
    size_t numPages, numFrames, pageSize, noOfProcesses;
    size_t bitsForPageNumber, bitsForOffset; // for decoding the location
    std::vector<Process> processes;
    std::vector<bool> frames;

    void printInitialSetup();
    void displayPageTables();
    size_t getPageNumber(size_t loc);
    size_t getPhysicalAddr(size_t loc, size_t procNum, size_t pageNum);
    int handlePageFault(size_t pageNum, size_t procNum, char ref);
    void findPageToEvict(size_t& procNum, int& pageIdx);
    void ageCounters();

public:
    PagingSimulator(std::string filename);
    void run();
    
};

#endif
