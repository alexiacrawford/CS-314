#include <stdio.h>
#include <stdlib.h>

int ge(float x, float y) {
    unsigned int ux = *((unsigned int*) &x); // convert x raw bits
    unsigned int uy = *((unsigned int*) &y); // convert y raw bits
    unsigned int sx = ux >> 31; // extract sign bit of ux
    unsigned int sy = uy >> 31; // extract sign bit of uy   
    ux &= 0x7FFFFFFF; // drop sign bit of ux
    uy &= 0x7FFFFFFF; // drop sign bit of uy
    return (ux == 0 && uy == 0) // returns one if both x and y are 0
    || (sx < sy)  // x is positive y is negative
    || (sx == 0 && sy == 0 && ux >= uy) // both are positive, figure out which is larger
    || (sx == 1 && sy == 1 && ux <= uy); //both are negative, figure out which is greater
}



int main(int argc, char *argv[]) {
  if (argc == 3) {
    float x = strtof(argv[1], NULL);
    float y = strtof(argv[2], NULL);
    printf("ge(%f, %f): %d", x, y, ge(x, y));
  } else {
    printf("%d\n", ge(0.0f, 0.0f)); //: 1
    printf("%d\n", ge(-0.0f, 0.0f)); //: 1
    printf("%d\n", ge(0.0f, -0.0f)); //: 1
    printf("%d\n", ge(-0.0f, -0.0f));  //: 1
    printf("%d\n", ge(1.0f, 1.0f)); //: 1
    printf("%d\n", ge(-1.0f, 1.0f)); //: 0
    printf("%d\n", ge(1.0f, -1.0f)); //: 1
    printf("%d\n", ge(-1.0f, -1.0f)); //: 1
    printf("%d\n", ge(-1.0f, 0.0f)); //: 0
    printf("%d\n", ge(0.0f, -1.0f)); //: 1
    printf("%d\n", ge(1.0f, 0.0f)); //: 1
    printf("%d\n", ge(0.0f, 1.0f)); //: 0
    printf("%d\n", ge(1.0f, 2.0f)); //: 0
    printf("%d\n", ge(2.0f, 1.0f)); //: 1
    printf("%d\n", ge(-1.0f, -2.0f)); //: 1
    printf("%d\n", ge(-2.0f, -1.0f)); //: 0
    }
    return 0;
}
