#ifndef COUNTER_H
#define COUNTER_H

#include <cstdint>
#include <string>

class Counter
{
private:
    uint8_t agingCounter;

public:
    Counter();
    void insertBitToLeft(bool bit);
    std::string getStrValue();
    size_t getValue();
    void reset();

};

#endif
