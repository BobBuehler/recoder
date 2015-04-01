#include <stdint.h>

#ifndef RECODER
#define RECODER

// Convert a unicode code point into the utf8 sequence of bytes
// Preconditions: codePoint is a valid unicode code point.
// bytes is long enough to store the bytes (maximum of 4).
// Postconditions: bytes contains the utf8 encoded bytes.
// The number of bytes used is returned.
int utf8_encode(uint32_t codePoint, uint8_t* bytes);

// Convert a sequence of utf8 bytes to the unicode code point
// Preconditions: bytes is a valid sequence of utf8.
// Postconditions: The unicode code point is returned.
uint32_t utf8_decode(uint8_t* bytes);

#endif