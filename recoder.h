#include <stdint.h>

#ifndef RECODER
#define RECODER

uint8_t getBits(uint32_t codePoint, int start, int count);
uint8_t setLeadingBits(uint8_t byte, int count);
int getLeadingOneCount(uint8_t byte);
uint32_t concatBits(uint32_t left, uint8_t right, int count);

int getUtf8ByteCount(uint32_t codePoint);

int encode(uint32_t codePoint, uint8_t* bytes);
uint32_t decode(uint8_t* bytes);

#endif