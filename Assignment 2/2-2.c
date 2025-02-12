#include <stdio.h>
#include <stdlib.h>

unsigned int extract (unsigned int x, int i){
    unsigned int byte = x >> (i * 8); //shift byte to least significant position
    byte = byte & 0xFF; //extract LSB
    return (int) (byte << 24) >> 24; // use 24 because it shifts byte to MSB, then sign extends, also learned from gooks for geeks
}


int main(int argc, char *argv[]) {
  if (argc == 3) {
    unsigned int x = strtoul(argv[1], NULL, 16);
    int i = strtol(argv[2], NULL, 10);
    printf("extract(%X, %d): 0x%08X", x, i, extract(x, i));
  } else {
    printf("0x%08X\n", extract(0x12345678, 0)); //: 0x00000078
    printf("0x%08X\n", extract(0xF2345678, 0)); //: 0x00000078
    printf("0x%08X\n", extract(0xABCDEF00, 2)); //: 0xFFFFFFCD
    printf("0x%08X\n", extract(0x0BCDEF00, 2)); //: 0xFFFFFFCD
  }
  return 0;
}
