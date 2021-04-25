#include <iostream>
#include <cmath>
#include "Process.h"

using std::cout;

Process::Process(uint32_t noOfPages, uint32_t noOfFrames)
{
    this->noOfPages = noOfPages;
    this->noOfFrames = noOfFrames;

    // noOfFrames is a power of 2
    // noOfFrames = 2^x
    // log (noOfFrames) = log(2^x)
    // log (noOfFrames) = x log(2)
    // So, x = log(noOfFrames) / log (2)
    // Or, x = log2(noOfFrames)
    size_t noOfBits = (size_t) (log10(noOfFrames) / log10(2));

    for (uint32_t i = 0; i < noOfPages; i++)
    {
        PageTableEntry pte(noOfBits);
        this->pageTable.push_back(pte);
    }

    for (uint32_t i = 0; i < noOfPages; i++)
    {
        Counter c;
        this->counters.push_back(c);
    }
}

void Process::printPageTable()
{
    cout << "page#\tR\tM\tP\tframe#\taging\n";
    for (uint32_t i = 0; i < this->noOfPages; i++)
    {
        cout << i << ":\t";
        if (this->pageTable[i].isPresent()) {
            cout << this->pageTable[i].getR() << '\t';
            cout << this->pageTable[i].getM() << '\t';
            cout << this->pageTable[i].getP() << '\t';
            cout << this->pageTable[i].getPageFrameNumber() << '\t';
            cout << this->counters[i].getStrValue() << '\n';
        } else {
            cout << "0\t0\t0\t-\n";
        }
    }
    cout << '\n';
}

void Process::removePageTableEntry(int idx)
{
    this->pageTable[idx].reset();
}
