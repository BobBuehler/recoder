// Simple program to test the enocode and decode methods of recoder

#include <stdio.h>

#include "recoder.h"

void testRecoder(uint32_t codePoint);
void toBinaryString(uint32_t value, int count, char* string);

int main() {
    printf("----------\n");
    testRecoder(50);
    printf("----------\n");
    testRecoder(150);
    printf("----------\n");
    testRecoder(1500);
    printf("----------\n");
    testRecoder(15000);
    printf("----------\n");
    testRecoder(150000);
    printf("----------\n");
    testRecoder(1500000);
    printf("----------\n");
    testRecoder(15000000);
    printf("----------\n");

    return 0;
}

// Flex recoder's encode and decode method on the given code point
// Preconditions: None
// Postconditions: recoder's results are printed to stdout.
void testRecoder(uint32_t codePoint)
{
    uint8_t bytes[4];
    int count = utf8_encode(codePoint, bytes);
    int decoded = utf8_decode(bytes);
    
    char binary[33];
    toBinaryString(codePoint, 32, binary);
    printf("codePoint: %08d | %08X | %s\n", codePoint, codePoint, binary);
    
    int i;
    for(i = 0; i < count; ++i)
    {
        toBinaryString(bytes[i], 8, binary);
        printf("byte[%d]:   %08d | %02X | %s\n", i, bytes[i], bytes[i], binary);
    }
    
    toBinaryString(decoded, 32, binary);
    printf("decoded:   %08d | %08X | %s\n", decoded, decoded, binary);
    
    printf(codePoint == decoded ? "PASS\n" : "FAIL\n");
}

// Convert a number to a binary string with a fixed number of digits
// Preconditions: string is at least length count + 1.
// Postconditions: string is a null-terminated string of 1s and 0s.
void toBinaryString(uint32_t value, int count, char* string)
{
    uint32_t mask = 1 << (count - 1);
    int i;
    for (i = 0; i < count; ++i)
    {
        string[i] = (value & (mask >> i)) != 0 ? '1' : '0';
    }
    string[count] = '\0';
}
