#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include "PageTableEntry.h"
#include "Counter.h"

class PagingSimulator; // forward declaration
class Process
{
private:
    uint32_t noOfPages;
    uint32_t noOfFrames;
    std::vector<PageTableEntry> pageTable;
    std::vector<Counter> counters;
    friend class PagingSimulator;


public:
    Process(uint32_t noOfPages, uint32_t noOfFrames);
    void printPageTable();
    void removePageTableEntry(int idx);

};

#endif
