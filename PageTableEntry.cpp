#include "PageTableEntry.h"

PageTableEntry::PageTableEntry(size_t noOfPageFrameBits)
{
    this->noOfPageFrameBits = noOfPageFrameBits;
    this->entry = 0;
}

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

uint32_t PageTableEntry::getR()
{
    uint32_t copyOfEntry = this->entry;
    copyOfEntry = copyOfEntry >> 31; // right shift by 31 bits
    copyOfEntry = copyOfEntry & 1;
    // entry:  R010...0
    // >> right shift 31 bits
    // entry : 000R
    //       & 0001
    // ------------
    //         000R
    return copyOfEntry;
}

void PageTableEntry::setR(bool flag)
{
    uint32_t msb1 = 2147483648; // binary 10000000000000000000000000000000
                                // msb - 1 = 01111111111111111111111111111111
    if (flag) {
        this->entry = this->entry | msb1;
    } else {
        this->entry = this->entry & (msb1 - 1);
    }
}

uint32_t PageTableEntry::getM()
{
    uint32_t copyOfEntry = this->entry;
    copyOfEntry = copyOfEntry >> 30;
    copyOfEntry = copyOfEntry & 1;
    return copyOfEntry;
}

void PageTableEntry::setM(bool flag)
{
    uint32_t msb1 = 1073741824; // binary 01000000000000000000000000000000
    if (flag) {
        this->entry = this->entry | msb1;
    } else {
        this->entry = this->entry & (msb1 - 1);
    }
}

uint32_t PageTableEntry::getP()
{
    uint32_t copyOfEntry = this->entry;
    copyOfEntry = copyOfEntry >> 29;
    copyOfEntry = copyOfEntry & 1;
    return copyOfEntry;
}

void PageTableEntry::setP(bool flag)
{
    uint32_t msb1 = 536870912; // binary 00100000000000000000000000000000
    if (flag) {
        this->entry = this->entry | msb1;
    } else {
        this->entry = this->entry & (msb1 - 1);
    }
}

uint32_t PageTableEntry::getPageFrameNumber()
{
    std::bitset<32> copyOfEntry(this->entry);
    uint32_t number = copyOfEntry[this->noOfPageFrameBits - 1];

    for (int i = this->noOfPageFrameBits - 2; i >= 0; i--)
    {
        number = number << 1;
        number = number | copyOfEntry[i];
    }

    return number;
}

void PageTableEntry::setPageFrameNumber(uint32_t number)
{
    this->entry = this->entry >> this->noOfPageFrameBits; // discard all page frame bits
    this->entry = this->entry << this->noOfPageFrameBits; // now put 0s in their place
    this->entry = this->entry | number; // then put the number in their place
}

size_t PageTableEntry::getNumberOfPageFrameBits()
{
    return this->noOfPageFrameBits;
}

void PageTableEntry::reset()
{
    this->entry = 0;
}

bool PageTableEntry::isPresent()
{
    std::bitset<32> copyOfEntry(this->entry);
    return copyOfEntry[29];
}
