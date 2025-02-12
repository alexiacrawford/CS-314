#include <stdio.h>

void printBytes(unsigned char *start, int len) { 
    for (int i = 0; i < len; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}
/* 1) I think that this function will print out a hexadecimal bytes (a-f) of the length of 
the given input (array). the *start is a pointer with a type of unsigned char. the len is the length of bytes being printed. 
Then the %.2x is the format for the output which is 2 characters and lowercase hex. the \n prints a new line. */

void printInt(int x) {
    printBytes((unsigned char *) &x, sizeof(int));
}
/*These look like little Endian representation, which we discussed in class and chapter 2.
the least significant byte was printed first (78). */

void printFloat(float x) {
    printBytes((unsigned char *) &x, sizeof(float));
}
/*This will print the byte representation of the given float*/

int main() {
    int sampleInt = 0x12345678; //Example value
    printf("Integer bytes:\n");
    printInt(sampleInt); //calling printInt

    float sampleFloat = 1.5; //Example value
    printf("Float bytes:\n");
    printFloat(sampleFloat); //Call printFloat

    return 0;
}