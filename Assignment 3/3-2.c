#include <stdio.h>
#include <stdlib.h>

// f(long, long, long):
//     subq    %rdx, %rdi        # x -= z
//     imulq   %rsi, %rdx        # temp = y * z
//     movq    %rdi, %rax        # rax = x (after x -= z)
//     andq    %rdx, %rax        # rax &= temp (y * z)
//     ret                       # return rax

//%rdi (x), %rsi (y), %rdx (z) %rax (v) 

long f(long x, long y, long z) {
    x -= z; // subq
    z *= y; // imulq
    long v = x; // movq
    v = (v & z); // andq
    return v;
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
        long x = strtol(argv[1], NULL, 10);
        long y = strtol(argv[2], NULL, 10);
        long z = strtol(argv[3], NULL, 10);
        printf("f(%ld, %ld, %ld): %ld\n", x, y, z, f(x, y, z));
    } else {
        // Hardcoded test cases
        printf("f(1, 2, 4): %ld\n", f(1, 2, 4));     // 8
        printf("f(3, 5, 7): %ld\n", f(3, 5, 7));     // 32
        printf("f(10, 20, 40): %ld\n", f(10, 20, 40)); // 800
        printf("f(30, 50, 70): %ld\n", f(30, 50, 70)); // 3464
        printf("f(30, 50, -70): %ld\n", f(30, 50, -70)); //68
    }
    return 0;
}