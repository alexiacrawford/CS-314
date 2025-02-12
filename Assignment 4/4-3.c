#include <stdio.h>
#include <stdlib.h>

void transpose(long a[4][4]) {
  for (long i = 0; i < 4; ++i) {
    for (long j = 0; j < i; ++j) {
      long t1 = a[i][j];
      long t2 = a[j][i];
      a[i][j] = t2;
      a[j][i] = t1;
    }
  } 
}

/* .L3:
        movq    (%rax), %rcx // %rcx = a[i][j], move value to t1
        movq    (%rdx), %rsi // %rsi = a[j][i], move value to t2
        movq    %rsi, (%rax) // a[i][j] == a[j][i]
        movq    %rcx, (%rdx) //  a[j][i] == a[i][j]
        addq    $8, %rax    // move to next a[i][j] element
        addq    $32, %rdx   // move to next a[j][i] element
*/

void transposeOpt(long a[4][4]) {
  for (long i = 0; i < 4; ++i) {
    long *rp = &a[i][0];
    long *cp = &a[0][i];
    for (long j = 0; j < i; ++j) {
      long t1 = *rp;             // t1 = a[i][j]
      long t2 = *cp;             // t2 = a[j][i]
      *rp = t2;                  //  a[i][j] = t2
      *cp = t1;                  // a[j][i] = t1
      rp++;                      // next element in the row
      cp += 4;                   // next element in the column
    }
  }
}

/* 
transposeOpt:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-56], rdi
        mov     QWORD PTR [rbp-8], 0
        jmp     .L2
.L5:
        mov     rax, QWORD PTR [rbp-8]
        sal     rax, 5
        mov     rdx, rax
        mov     rax, QWORD PTR [rbp-56]
        add     rax, rdx
        mov     QWORD PTR [rbp-16], rax
        mov     rax, QWORD PTR [rbp-8]
        lea     rdx, [0+rax*8]
        mov     rax, QWORD PTR [rbp-56]
        add     rax, rdx
        mov     QWORD PTR [rbp-24], rax
        mov     QWORD PTR [rbp-32], 0
        jmp     .L3
.L4:
        mov     rax, QWORD PTR [rbp-16]
        mov     rax, QWORD PTR [rax]
        mov     QWORD PTR [rbp-40], rax
        mov     rax, QWORD PTR [rbp-24]
        mov     rax, QWORD PTR [rax]
        mov     QWORD PTR [rbp-48], rax
        mov     rax, QWORD PTR [rbp-16]
        mov     rdx, QWORD PTR [rbp-48]
        mov     QWORD PTR [rax], rdx
        mov     rax, QWORD PTR [rbp-24]
        mov     rdx, QWORD PTR [rbp-40]
        mov     QWORD PTR [rax], rdx
        add     QWORD PTR [rbp-16], 8
        add     QWORD PTR [rbp-24], 32
        add     QWORD PTR [rbp-32], 1
.L3:
        mov     rax, QWORD PTR [rbp-32]
        cmp     rax, QWORD PTR [rbp-8]
        jl      .L4
        add     QWORD PTR [rbp-8], 1
.L2:
        cmp     QWORD PTR [rbp-8], 3
        jle     .L5
        nop
        nop
        pop     rbp
        ret
        */

void print(long a[4][4]) {
  for (int i = 0; i < 4; ++i) {
    for (int j =  0; j < 4; ++j) {
      printf("%ld ", a[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc == 17) {
    long a[4][4]; //4x4 matrix
    long b[4][4]; //4x4 matrix
    for (int i = 0; i < 4; ++i) { //loop through each row
      for (int j = 0; j < 4; ++j) { //loop through each column
        a[i][j] = strtol(argv[i * 4 + j + 1], NULL, 10); //convert to long int and store in a[i][j]
        b[i][j] = a[i][j]; //copy value
      }
    }
    transpose(a);
    printf("transpose(a)\n");
    print(a);
    transposeOpt(b);
    printf("trasnposeOpt(b)\n");
    print(b);
  } else {
    long a[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}
    };
    long b[4][4] = {
      {1, 2, 3, 4}, {5, 6, 7, 8},  {9, 10, 11, 12}, {13, 14, 15, 16}
    };
    printf("Original:\n");
    print(a);
    transpose(a);
    printf("\ntranspose(a)\n");
    print(a);
    transposeOpt(b);
    printf("\ntransposeOpt(b)\n");
    print(b);
 
  }
  return 0;
}