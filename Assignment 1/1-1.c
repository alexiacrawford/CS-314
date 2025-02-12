#include <stdio.h>
#include <stdlib.h>

unsigned int combine (unsigned int x, unsigned int y) {
    unsigned int x_byte = x & 0xFF000000; //isolates byte 3
    unsigned int y_byte = y & 0x00FFFFFF; //isolates byte 2

    return x_byte | y_byte; //combines extracted bytes
}


int main(int argc, char *argv[]) {
  if (argc == 3) {
    unsigned int x = strtoul(argv[1], NULL, 16);
    unsigned int y = strtoul(argv[2], NULL, 16);
    printf("combine(%X, %X): %X", x, y, combine(x, y));
  } else {
    printf("0x%X\n", combine(0x12345678, 0xABCDEF00)); //0x12CDEF00;
    printf("0x%X\n", combine(0xABCDEF00, 0x12345678)); //0xAB345678;
  }
  return 0;
}