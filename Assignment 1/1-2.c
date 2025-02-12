#include <stdio.h>
#include <stdlib.h>

unsigned int replace (unsigned int x, int i, unsigned char b){
    unsigned int mask = 0xff << (i*8); //shifts byte to selected position
    unsigned int x2 = x & ~mask; //flips all bits
    x2 |= (b<<(i*8)); //shifts byte to selected location and places it in x2's spot
    return x2;
}

int main(int argc, char *argv[]) {
  if (argc == 4) {
    unsigned int x = strtoul(argv[1], NULL, 16);
    int i = strtol(argv[2], NULL, 10);
    unsigned char b = (unsigned char)strtoul(argv[3], NULL, 16);
    printf("replace(%X, %d, %X): %X", x, i, b, replace(x, i, b));
  } else {
    printf("0x%X\n", replace(0x12345678, 3, 0xAB)); //0xAB345678
    printf("0x%X\n", replace(0x12345678, 2, 0xAB)); //0x12AB5678
    printf("0x%X\n", replace(0x12345678, 1, 0xAB)); //0x1234AB78
    printf("0x%X\n", replace(0x12345678, 0, 0xAB)); //0x123456AB
  }
  return 0;
}
