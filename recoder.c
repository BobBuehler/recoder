#include "recoder.h"

// Get a number made from a substring of bits from another number
// start specifies the least significant bit to retrieve.
// count specifies the number of bits of increasing significance to retrieve.
// Preconditions: start and count are non-negative.
// start + count does not esceed 32.
// Postconditions: returns 
uint32_t getBits(uint32_t codePoint, int start, int count)
{
    codePoint >>= start;
    uint32_t mask = (1 << count) - 1;
    return (uint8_t) (codePoint & mask);
}

uint8_t setLeadingBits(uint8_t byte, int count)
{
    uint32_t mask = ~0 << (8 - count);
    return (uint8_t) byte | mask;
}

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

uint32_t concatBits(uint32_t left, uint8_t right, int count)
{
    left = left << count;
    uint32_t mask = (1 << count) - 1;
    return left | (right & mask);
}


int getUtf8ByteCount(uint32_t codePoint)
{
    if (codePoint <= 0x7F)
        return 1;
    else if (codePoint <= 0x7FF)
        return 2;
    else if (codePoint <= 0xFFFF)
        return 3;
    else if (codePoint <= 0x1FFFFF)
        return 4;
    else
        return 0;
}

// see recoder.h for docs
int utf8_encode(uint32_t codePoint, uint8_t* bytes)
{
    int count = getUtf8ByteCount(codePoint);
    switch (count)
    {
        case 1:
            bytes[0] = getBits(codePoint, 0, 7);
            break;
        case 2:
            bytes[0] = getBits(codePoint, 6, 5);
            bytes[0] = setLeadingBits(bytes[0], 2);
            bytes[1] = getBits(codePoint, 0, 6);
            bytes[1] = setLeadingBits(bytes[1], 1);
            break;
        case 3:
            bytes[0] = getBits(codePoint, 12, 4);
            bytes[0] = setLeadingBits(bytes[0], 3);
            bytes[1] = getBits(codePoint, 6, 6);
            bytes[1] = setLeadingBits(bytes[1], 1);
            bytes[2] = getBits(codePoint, 0, 6);
            bytes[2] = setLeadingBits(bytes[2], 1);
            break;
        case 4:
            bytes[0] = getBits(codePoint, 18, 3);
            bytes[0] = setLeadingBits(bytes[0], 4);
            bytes[1] = getBits(codePoint, 12, 6);
            bytes[1] = setLeadingBits(bytes[1], 1);
            bytes[2] = getBits(codePoint, 6, 6);
            bytes[2] = setLeadingBits(bytes[2], 1);
            bytes[3] = getBits(codePoint, 0, 6);
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
    uint32_t codePoint;
    switch (getLeadingOneCount(bytes[0])) {
        case 0:
            codePoint = bytes[0];
            break;
        case 2:
            codePoint = getBits(bytes[0], 0, 5);
            codePoint = concatBits(codePoint, getBits(bytes[1], 0, 6), 6);
            break;
        case 3:
            codePoint = getBits(bytes[0], 0, 4);
            codePoint = concatBits(codePoint, getBits(bytes[1], 0, 6), 6);
            codePoint = concatBits(codePoint, getBits(bytes[2], 0, 6), 6);
            break;
        case 4:
            codePoint = getBits(bytes[0], 0, 3);
            codePoint = concatBits(codePoint, getBits(bytes[1], 0, 6), 6);
            codePoint = concatBits(codePoint, getBits(bytes[2], 0, 6), 6);
            codePoint = concatBits(codePoint, getBits(bytes[3], 0, 6), 6);
            break;
        default:
            codePoint = 0;
            break;
    }
    return codePoint;
}

