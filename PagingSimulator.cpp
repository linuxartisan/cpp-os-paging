#include <iostream>
#include <sstream>
#include <cmath>
#include <bitset>
#include <climits>
#include "PagingSimulator.h"

using namespace std;

PagingSimulator::PagingSimulator(std::string filename)
{
    this->fs.open(filename);

    if (!this->fs.is_open()) {
        this->noOfProcesses = 0;
        return;
    }

    string line;

    // read line 1
    getline(this->fs, line);
    istringstream ss(line);
    ss >> this->numPages >> this->numFrames >> this->pageSize;

    // e.g. vir mem size = 512
    // 2^x = 512
    // x = 9
    size_t bitsForLogicalAddr = (size_t) (log10(this->numPages * this->pageSize) / log10(2));
    this->bitsForPageNumber = (size_t) (log10(numPages) / log10(2));
    this->bitsForOffset = bitsForLogicalAddr - this->bitsForPageNumber;

    // read line 2
    getline(this->fs, line);
    ss.str(line); // give line to ss
    ss.seekg(0);  // set ss to beginning of line
    ss >> this->noOfProcesses;

    // create processes
    for (size_t i = 0; i < this->noOfProcesses; i++)
    {
        Process p(this->numPages, this->numFrames);
        this->processes.push_back(p);
    }

    // create (empty) frames
    for (size_t i = 0; i < this->numFrames; i++)
    {
        this->frames.push_back(false);
    }

    this->printInitialSetup();
}

void PagingSimulator::run()
{
    string line;
    size_t procNum, location;
    char ref;
    int aging = 0;

    // read each virtual memory reference
    while (getline(this->fs, line)) {
        istringstream ss(line);
        ss >> procNum >> ref >> location; // e.g. 0 r 100

        cout << "Process " << procNum << " requests " << ref << ' ' << location << '\n';

        // check the page number
        size_t pageNum = this->getPageNumber(location);
        cout << "Page number: " << pageNum << '\n';

        // if this page table entry is absent
        int frameNum;
        if (!this->processes[procNum].pageTable[pageNum].isPresent()) {
            // handle page fault
            frameNum = this->handlePageFault(pageNum, procNum, ref);
        } else {
            this->processes[procNum].pageTable[pageNum].setR(true);
            // get frame number
            frameNum = this->processes[procNum].pageTable[pageNum].getPageFrameNumber();
        }

        cout << "Frame number: " << frameNum << '\n';
        cout << "Physical address: " << this->getPhysicalAddr(location, procNum, pageNum) << '\n';
        this->displayPageTables();

        aging++;
        if (aging == 2) {
            cout << "Aging the counters ...\n\n";
            this->ageCounters();
            aging = 0;
        }
    }

    this->fs.close();
}

void PagingSimulator::printInitialSetup()
{
    cout << "INITIAL TABLE SETUP:\n";
    cout << "Virtual Memory Size: " << this->numPages * this->pageSize << '\n';
    cout << "Physical Memory Size: " << this->numFrames * this->pageSize << '\n';
    cout << "Page Size: " << this->pageSize << '\n';
    cout << "Number of Processes: " << this->noOfProcesses << '\n';
    cout << "Number of Pages: " << this->numPages << '\n';
    cout << "Number of Frames: " << this->numFrames << '\n';
    this->displayPageTables();
}

void PagingSimulator::displayPageTables()
{
    cout << "Page Tables (with aging status)\n";

    for (size_t i = 0; i < this->noOfProcesses; i++)
    {
        cout << "Process " << i << '\n';
        this->processes[i].printPageTable();
    }
}

/**
 * Size of Logical address  = 2^m
 * Number of pages          = x
 * Bits for page number     = n
 *   where n = log2(x)
 *
 * ---------------------------------------
 * |   page number    |      offset      | : logical address (loc)
 * ---------------------------------------
 *         n                  m - n        : length = m
 */
size_t PagingSimulator::getPageNumber(size_t loc)
{
    bitset<32> location(loc);
    location >>= this->bitsForOffset;
    return (size_t) location.to_ulong();
}

size_t PagingSimulator::getPhysicalAddr(size_t loc, size_t procNum, size_t pageNum)
{
    bitset<32> location_bitset(loc);

    // clear out the bits for page number
    location_bitset <<= 32 - this->bitsForOffset;
    location_bitset >>= 32 - this->bitsForOffset;

    uint32_t pfNum = this->processes[procNum].pageTable[pageNum].getPageFrameNumber();
    bitset<32> pfNum_bitset(pfNum); // e.g. 0000000010
    bitset<32> mask;                // mask 0000000000
    mask |= pfNum_bitset;           // mask 0000000010
    mask <<= this->bitsForOffset;   // mask 001000...0

    location_bitset |= mask;        // loc  0010xx...x

    return (size_t) location_bitset.to_ulong();
}

int PagingSimulator::handlePageFault(size_t pageNum, size_t procNum, char ref)
{
    cout << "Page fault ...\n";

    // find an empty frame
    int idx = -1;
    for (size_t i = 0; i < this->numFrames; i++)
    {
        if (!this->frames[i]) {
            // found an empty frame
            idx = i;
            this->frames[i] = true;
            break;
        }
    }

    // if no frame is empty, we need to evict a page
    if (idx == -1) {
        size_t evictedProcNum; // process whose page is evicted
        int evictedPageIdx;    // the page that gets evicted

        // find counter with least value
        this->findPageToEvict(evictedProcNum, evictedPageIdx);

        // evict the page
        cout << "Evicting process " << evictedProcNum << " page " << evictedPageIdx << '\n';
        idx = this->processes[evictedProcNum].pageTable[evictedPageIdx].getPageFrameNumber();
        if (this->processes[evictedProcNum].pageTable[evictedPageIdx].getM()) {
            cout << "Writing frame " << idx << " back to disk:\n";
        }
        this->processes[evictedProcNum].pageTable[evictedPageIdx].reset();
        this->processes[evictedProcNum].counters[evictedPageIdx].reset();
    }

    cout << "Loading page " << pageNum << " of process " << procNum << " into frame " << idx << '\n';

    this->processes[procNum].pageTable[pageNum].setR(true);
    this->processes[procNum].pageTable[pageNum].setP(true);
    if (ref == 'w') {
        this->processes[procNum].pageTable[pageNum].setM(true);
    }
    this->processes[procNum].pageTable[pageNum].setPageFrameNumber(idx);
    this->processes[procNum].counters[pageNum].reset();

    return idx;
}

void PagingSimulator::findPageToEvict(size_t& procNum, int& pageIdx)
{
    pageIdx = -1;
    procNum = UINT_MAX;
    size_t min = UINT_MAX;
    for (size_t i = 0; i < this->noOfProcesses; i++) {
        for (size_t j = 0; j < this->numPages; ++j)
        {
            // cout << "before: min: " << min << '\t' << "i: " << i << '\n';
            if (this->processes[i].pageTable[j].isPresent()) {
                size_t v = this->processes[i].counters[j].getValue();
                if (v < min) {
                    min = v;
                    procNum = i;
                    pageIdx = (int) j;
                }
            }
            // cout << "after: min: " << min << '\t' << "i: " << i << '\n';
        }
    }
    // cout << "idx: " << idx << '\n';
}

void PagingSimulator::ageCounters()
{
    for (size_t i = 0; i < this->noOfProcesses; i++)
    {
        for (size_t j = 0; j < this->processes[i].noOfPages; j++)
        {
            if (this->processes[i].pageTable[j].isPresent()) {
                this->processes[i].counters[j].insertBitToLeft(this->processes[i].pageTable[j].getR());
                this->processes[i].pageTable[j].setR(false);
            }
        }

        // cout << "\nDEBUG:\n";
        // this->processes[i].printPageTable();
    }
}
