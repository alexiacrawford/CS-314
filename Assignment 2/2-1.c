#include <stdio.h>
#include <stdlib.h>

unsigned int mask(int n){ //return bit mask containing 1s for least significant n bits
    return (1 << n) -1; // shifts 1 left by n places, essentially 2^n, - 1 sets all zeros after 1 to a 1
} 


int main(int argc, char *argv[]) {
  if (argc == 2) {
    int n = strtol(argv[1], NULL, 10);
    printf("mask(%d): %X", n, mask(n));
  } else {
    printf("%X\n", mask(1)); // 1
    printf("%X\n", mask(2)); //: 3
    printf("%X\n", mask(3)); //: 7
    printf("%X\n", mask(5)); //: 1F
    printf("%X\n", mask(8)); //: FF
    printf("%X\n", mask(16)); //: FFFF
    printf("%X\n", mask(31)); //: 7FFFFFFF
  }
  return 0;
}

// I learend the -1 trick on Geeks for geeks, https://www.geeksforgeeks.org/bit-tricks-competitive-programming/?ref=gcse_outind