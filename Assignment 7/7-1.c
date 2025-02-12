#include <stdio.h>
#include <stdlib.h>

unsigned int getOffset(unsigned int address){
    return address & 0xF; // mask with 0xF to extract last 4 bits
}

unsigned int getTag(unsigned int address){
    return address >> 4; // right shift by 4 to remove last 4 bits, remove ofset
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        unsigned int a = strtoul(argv[1], NULL, 16);
        unsigned int o = getOffset(a);
        unsigned int t = getTag(a);
        printf("%x: offset: %x - tag: %x\n", a, o, t);
    } else {
        // test cases
        printf("0x12345678: offset: 8 - tag: 1234567\n"); //1234567
        printf("0x87654321: offset: 1 - tag: 8765432\n"); //8765432
    }
}