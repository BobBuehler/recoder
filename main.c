#include <stdio.h>

#include "recoder.h"

void textPrompt(char* prompt, char* dst, int size)
{
    // print some text
    fputs(prompt, stdout);
    fflush(stdout);
    
    // read some text
    fgets(dst, size, stdin);
    
    // clean off the trailing newline
    int i;
    for(i = 0; i < size; ++i)
    {
        if (dst[i] == '\n')
            dst[i] = 0;
        if (dst[i] == 0)
            return;
    }
}

void testRecoder(uint32_t codePoint)
{
    printf("TEST\ncodePoint: %d\n", codePoint);
    
    uint8_t bytes[4];
    int count = encode(codePoint, bytes);
    int i;
    for(i = 0; i < count; ++i)
    {
        printf("byte[%d]: %d\n", i, bytes[i]);
    }
    
    int decoded = decode(bytes);
    printf("decoded: %d\n", decoded);
}

int main() {
    char text[100];
    //textPrompt("Enter some text to recode: ", text, sizeof text);
    //printf("text: %s\n", text);

    testRecoder(50);
    
    testRecoder(150);
    
    testRecoder(1500);
    
    testRecoder(15000);
    
    testRecoder(150000);
    
    testRecoder(1500000);
    
    testRecoder(15000000);

    return 0;
}
