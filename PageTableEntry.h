#ifndef PAGETABLEENTRY_H
#define PAGETABLEENTRY_H

#include <cstdint>
#include <bitset>

/**
 * A page table entry consists of 32 bits.
 * R M P <---- Page frame number ---->
 * x x x xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * where,
 * R = Referenced bit
 * M = Modified bit
 * P = Present/absent bit
 * Rest all bits are for the page frame number
 */
class PageTableEntry
{
private:
    uint32_t entry;
    size_t  noOfPageFrameBits;

public:
    PageTableEntry(size_t noOfPageFrameBits);
    uint32_t getR();
    void setR(bool flag);
    uint32_t getM();
    void setM(bool flag);
    uint32_t getP();
    void setP(bool flag);
    uint32_t getPageFrameNumber();
    void setPageFrameNumber(uint32_t number);
    size_t getNumberOfPageFrameBits();
    void reset();
    bool isPresent();

};

#endif
