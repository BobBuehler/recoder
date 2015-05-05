#include "recoder.h"

// Get a number made from a substring of bits from another number.
// start specifies the least significant bit to retrieve.
// count specifies the number of bits of increasing significance to retrieve.
// Preconditions: start and count are non-negative.
// start + count does not exceed 32.
// Postconditions: returns a new number where the range of bits specified by
// start and count are copied from value and placed in the new number starting
// at bit zero.
uint32_t getBits(uint32_t value, int start, int count)
{
    value >>= start;
    uint32_t mask = (1 << count) - 1;
    return (uint8_t) (value & mask);
}

// Gets a number where the highest order bits in byte are set.
// count is the number of high order bits to set.
// Preconditions: count is between 0 and 8, inclusive.
// Postcondition: returns a new number which is the same as byte except the
// highest order bits are 1s.
uint8_t setLeadingBits(uint8_t byte, int count)
{
    uint32_t mask = ~0 << (8 - count);
    return (uint8_t) byte | mask;
}

// Gets the number of consecutive 1s in the highest order bits.
// Preconditions: none
// Postconditions: returns the number of 1s found in the highest order bits
// before a 0 is seen.
int getLeadingOneCount(uint8_t byte)
{
    uint8_t mask = 1 << 7;
    int count = 0;
    while ((byte & mask) != 0)
    {
        count++;
        mask = mask >> 1;
    }
    return count;
}

// Gets a number made from concatenating bits onto the value of left.
// count is the number of bits to take from right.
// Preconditions: left requires 32 - count bits to represent
// count is between 0 and 8, inclusive.
// Postconditions: returns the value of left shifted left and a number of bits
// from right placed in the least significant bits.
uint32_t concatBits(uint32_t left, uint8_t right, int count)
{
    left = left << count;
    uint32_t mask = (1 << count) - 1;
    return left | (right & mask);
}

// Gets the number of bytes required in UTF-8 to encode the codepoint
// Preconditions: none
// Postconditions: returns the number of bytes needed or returns -1 if the
// codepoint cannot be represented in UTF-8.
int getUtf8ByteCount(uint32_t codepoint)
{
    if (codepoint <= 0x7F)
        return 1;
    else if (codepoint <= 0x7FF)
        return 2;
    else if (codepoint <= 0xFFFF)
        return 3;
    else if (codepoint <= 0x1FFFFF)
        return 4;
    else
        return -1;
}

// see recoder.h for docs
int utf8_encode(uint32_t codepoint, uint8_t* bytes)
{
    int count = getUtf8ByteCount(codepoint);
    switch (count)
    {
        case 1:
            bytes[0] = getBits(codepoint, 0, 7);
            break;
        case 2:
            bytes[0] = getBits(codepoint, 6, 5);
            bytes[0] = setLeadingBits(bytes[0], 2);
            bytes[1] = getBits(codepoint, 0, 6);
            bytes[1] = setLeadingBits(bytes[1], 1);
            break;
        case 3:
            bytes[0] = getBits(codepoint, 12, 4);
            bytes[0] = setLeadingBits(bytes[0], 3);
            bytes[1] = getBits(codepoint, 6, 6);
            bytes[1] = setLeadingBits(bytes[1], 1);
            bytes[2] = getBits(codepoint, 0, 6);
            bytes[2] = setLeadingBits(bytes[2], 1);
            break;
        case 4:
            bytes[0] = getBits(codepoint, 18, 3);
            bytes[0] = setLeadingBits(bytes[0], 4);
            bytes[1] = getBits(codepoint, 12, 6);
            bytes[1] = setLeadingBits(bytes[1], 1);
            bytes[2] = getBits(codepoint, 6, 6);
            bytes[2] = setLeadingBits(bytes[2], 1);
            bytes[3] = getBits(codepoint, 0, 6);
            bytes[3] = setLeadingBits(bytes[3], 1);
            break;
        default:
            bytes[0] = 0;
            break;
    }
    return count;
}

// see recoder.h for docs
uint32_t utf8_decode(uint8_t* bytes) {
    uint32_t codepoint;
    switch (getLeadingOneCount(bytes[0])) {
        case 0:
            codepoint = bytes[0];
            break;
        case 2:
            codepoint = getBits(bytes[0], 0, 5);
            codepoint = concatBits(codepoint, getBits(bytes[1], 0, 6), 6);
            break;
        case 3:
            codepoint = getBits(bytes[0], 0, 4);
            codepoint = concatBits(codepoint, getBits(bytes[1], 0, 6), 6);
            codepoint = concatBits(codepoint, getBits(bytes[2], 0, 6), 6);
            break;
        case 4:
            codepoint = getBits(bytes[0], 0, 3);
            codepoint = concatBits(codepoint, getBits(bytes[1], 0, 6), 6);
            codepoint = concatBits(codepoint, getBits(bytes[2], 0, 6), 6);
            codepoint = concatBits(codepoint, getBits(bytes[3], 0, 6), 6);
            break;
        default:
            codepoint = 0;
            break;
    }
    return codepoint;
}

