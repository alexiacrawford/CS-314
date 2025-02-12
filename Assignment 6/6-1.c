#include <stdio.h>
#include <stdlib.h>

long f(long a, long b, long c, long d, long n) {

    //caluculate constant multiplications outside the loops
    long a_b = a * b; 
    long c_d = c * d; 

    long result = 0;

    for (long i = 0; i < n; i += 2) { //iterate over even values from i from 0 to n-2
        for (long j = 0; j < n; j += 2) { // iterate over even values j from 0 to n-2
            result += a_b + i * c_d + j; // O(1) multiplication
        }
    }
    return result;
}



int main(int argc, char *argv[]) {
    if (argc == 6) {
        long a = strtol(argv[1], NULL, 10);
        long b = strtol(argv[2], NULL, 10);
        long c = strtol(argv[3], NULL, 10);
        long d = strtol(argv[4], NULL, 10);
        long

 e = strtol(argv[5], NULL, 10);
        printf("f(%ld, %ld, %ld, %ld, %ld): %ld\n", a, b, c, d, e, f(a, b, c, d, e));
    } else {
        // Test cases
        printf("f(1, 2, 3, 4, 5): %ld\n", f(1, 2, 3, 4, 5)); // 252
        printf("f(2, 3, 4, 5, 6): %ld\n", f(2, 3, 4, 5, 6)); // 432
        printf("f(6, 5, 4, 3, 2): %ld\n", f(6, 5, 4, 3, 2)); // 30
        printf("f(5, 4, 3, 2, 1): %ld\n", f(5, 4, 3, 2, 1)); // 20
    }

    return 0;

}