#include <bitset>
#include "Counter.h"

using std::bitset;

Counter::Counter()
{
    this->agingCounter = 0;
}

/**
 * Modifies the counter.
 * Shifts all the bits to right by 1 place. Inserts a 0 or 1
 * in the MSB place.
 */
void Counter::insertBitToLeft(bool bit)
{
    uint8_t msb = 128; // binary 10000000
    this->agingCounter = this->agingCounter >> 1;

    if (bit) {
        this->agingCounter = this->agingCounter | msb;
    }
}

std::string Counter::getStrValue()
{
    bitset<8> bits(this->agingCounter);
    return bits.to_string();
}

size_t Counter::getValue()
{
	return (size_t) this->agingCounter;
}

void Counter::reset()
{
    this->agingCounter = 0;
}
