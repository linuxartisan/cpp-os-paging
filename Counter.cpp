#include <bitset>
#include "Counter.h"

using std::bitset;

Counter::Counter()
{
    this->agingCounter = 0;
}

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
