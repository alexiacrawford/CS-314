#include <stdio.h>
#include <stdlib.h>

int evenBit(unsigned int x){
    unsigned int mask = 0x55555555;
    return !!(x & mask); //first ! makes sure either a 0 or 1 is returned, second ! tells us the correct answer and negates the first value. I learned this from stack overflow. 

}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    unsigned int x = strtoul(argv[1], NULL, 16);
    printf("evenBit(%X): %X", x, evenBit(x));
  } else {
    printf("%x\n", evenBit(0x1)); //1
printf("%x\n", evenBit(0x2)); //0
printf("%x\n", evenBit(0x3)); //1
printf("%x\n", evenBit(0x4)); //1
printf("%x\n", evenBit(0xFFFFFFFF)); //1
printf("%x\n", evenBit(0xAAAAAAAA)); //0
printf("%x\n", evenBit(0x55555555)); //1
  }
  return 0;
}
