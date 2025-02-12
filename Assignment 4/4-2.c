#include <stdio.h>
#include <stdlib.h>

long iterativeFact(long x) {
    long result = 1;
    for (long i = 1; i <= x; i++) {
        result *= i;
    }

    return result;
}


/*iterativeFact:
        push    rbp     // push pointer to stack to save it
        mov     rbp, rsp
        mov     QWORD PTR [rbp-24], rdi
        mov     QWORD PTR [rbp-8], 1
        mov     QWORD PTR [rbp-16], 1
        jmp     .L2
.L3:
        mov     rax, QWORD PTR [rbp-8]
        imul    rax, QWORD PTR [rbp-16]
        mov     QWORD PTR [rbp-8], rax
        add     QWORD PTR [rbp-16], 1
.L2:
        mov     rax, QWORD PTR [rbp-16]
        cmp     rax, QWORD PTR [rbp-24]
        jle     .L3
        mov     rax, QWORD PTR [rbp-8]
        pop     rbp     // pop pointer back into rbp
        ret     // pop return address
*/



long recursiveFact(long x){
    if (x <= 1){
        return 1;
    }
    else 
    {
        return x * recursiveFact(x - 1);

    }

}

/*
recursiveFact:
        push    rbp     //push pointer to stack
        mov     rbp, rsp
        sub     rsp, 16
        mov     QWORD PTR [rbp-8], rdi
        cmp     QWORD PTR [rbp-8], 1
        jg      .L6
        mov     eax, 1
        jmp     .L7
.L6:
        mov     rax, QWORD PTR [rbp-8]
        sub     rax, 1
        mov     rdi, rax
        call    recursiveFact   // push return address to stack
        imul    rax, QWORD PTR [rbp-8]
.L7:
        leave   // pop pointer 
        ret     // pop return address
.LC0:
        .string "iterativeFact(%ld): %ld\n"
.LC1:
        .string "recursiveFact(%ld): %ld\n"
.LC2:
        .string "%ld\n"
*/

int main(int argc, char *argv[]) {
  if (argc == 2) {
    long x = strtol(argv[1], NULL, 10);
    printf("iterativeFact(%ld): %ld\n", x, iterativeFact(x));
    printf("recursiveFact(%ld): %ld\n", x, recursiveFact(x));
  } else {
    printf("%ld\n", iterativeFact(0)); //1
printf("%ld\n", recursiveFact(0)); //1
printf("%ld\n", iterativeFact(1)); //1
printf("%ld\n", recursiveFact(1)); //1
printf("%ld\n", iterativeFact(5)); //120
printf("%ld\n", recursiveFact(5)); //120
  }
  return 0;
}

/*
main:
        push    rbp     // push pointer to stack
        mov     rbp, rsp
        sub     rsp, 32
        mov     DWORD PTR [rbp-20], edi
        mov     QWORD PTR [rbp-32], rsi
        cmp     DWORD PTR [rbp-20], 2
        jne     .L9
        mov     rax, QWORD PTR [rbp-32]
        add     rax, 8
        mov     rax, QWORD PTR [rax]
        mov     edx, 10
        mov     esi, 0
        mov     rdi, rax
        call    strtol      // push return address for strtol
        mov     QWORD PTR [rbp-8], rax
        mov     rax, QWORD PTR [rbp-8]
        mov     rdi, rax
        call    iterativeFact   // push return address for iterativeFact
        mov     rdx, rax
        mov     rax, QWORD PTR [rbp-8]
        mov     rsi, rax
        mov     edi, OFFSET FLAT:.LC0
        mov     eax, 0
        call    printf      // push return address for printf
        mov     rax, QWORD PTR [rbp-8]
        mov     rdi, rax
        call    recursiveFact   // push the return address for recursiveFact
        mov     rdx, rax
        mov     rax, QWORD PTR [rbp-8]
        mov     rsi, rax
        mov     edi, OFFSET FLAT:.LC1
        mov     eax, 0
        call    printf
        jmp     .L10
.L9:
        mov     edi, 0
        call    iterativeFact
        mov     rsi, rax
        mov     edi, OFFSET FLAT:.LC2
        mov     eax, 0
        call    printf
        mov     edi, 0
        call    recursiveFact
        mov     rsi, rax
        mov     edi, OFFSET FLAT:.LC2
        mov     eax, 0
        call    printf
        mov     edi, 1
        call    iterativeFact
        mov     rsi, rax
        mov     edi, OFFSET FLAT:.LC2
        mov     eax, 0
        call    printf
        mov     edi, 1
        call    recursiveFact
        mov     rsi, rax
        mov     edi, OFFSET FLAT:.LC2
        mov     eax, 0
        call    printf
        mov     edi, 5
        call    iterativeFact
        mov     rsi, rax
        mov     edi, OFFSET FLAT:.LC2
        mov     eax, 0
        call    printf
        mov     edi, 5
        call    recursiveFact
        mov     rsi, rax
        mov     edi, OFFSET FLAT:.LC2
        mov     eax, 0
        call    printf
.L10:
        mov     eax, 0
        leave
        ret     // pop return address 
        */

