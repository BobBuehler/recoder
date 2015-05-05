#include <stdint.h>

#ifndef RECODER
#define RECODER

// Convert a Unicode codepoint into the utf8 sequence of bytes
// Preconditions: codepoint is a valid Unicode codepoint.
// bytes is long enough to store the bytes (maximum of 4).
// Postconditions: bytes contains the utf8 encoded bytes.
// The number of bytes used is returned.
int utf8_encode(uint32_t codepoint, uint8_t* bytes);

// Convert a sequence of utf8 bytes to the Unicode codepoint
// Preconditions: bytes starts with a character validly encoded in utf8.
// Postconditions: The Unicode codepoint is returned.
uint32_t utf8_decode(uint8_t* bytes);

#endif