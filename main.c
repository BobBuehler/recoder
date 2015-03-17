#include <stdio.h>

#include "recoder.h"

void toBinaryString(uint32_t byte, int count, char* string)
{
    uint32_t mask = 1 << (count - 1);
    int i;
    for (i = 0; i < count; ++i)
    {
        string[i] = (byte & (mask >> i)) != 0 ? '1' : '0';
    }
    string[count] = '\0';
}

void testRecoder(uint32_t codePoint)
{
    uint8_t bytes[4];
    int count = encode(codePoint, bytes);
    int decoded = decode(bytes);
    
    char binary[33];
    toBinaryString(codePoint, 32, binary);
    printf("codePoint: %d | %08X | %s\n", codePoint, codePoint, binary);
    
    toBinaryString(decoded, 32, binary);
    printf("decoded:   %d | %08X | %s\n", decoded, decoded, binary);
    
    int i;
    for(i = 0; i < count; ++i)
    {
        toBinaryString(bytes[i], 8, binary);
        printf("byte[%d]: %03d | %02X | %s\n", i, bytes[i], bytes[i], binary);
    }
}

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
