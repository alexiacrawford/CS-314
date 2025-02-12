#include <stdio.h>
#include <stdlib.h>

/*loop(long, long):
        movq    %rsi, %rcx  // moves value into %rcx, sets %rcx (shift count) to b
        movl    $2, %eax    // same as movq $2, %rax, set mask to 2, eax is lower 32bits of rax
        movl    $0, %edx    // same as movq $0, %rdx, set result to 0, edx is lower 32 bits of rdx
        jmp     .L2         // jump to .L2 which is a condition check
.L3:
        movq    %rax, %r8   // copy mask to %r8
        andq    %rdi, %r8   // do AND operation between a and mask, store at %r8
        orq     %r8, %rdx   // do OR operation into result
        salq    %cl, %rax   // same as salq %rcx, %rax, shift left by %cl which is b value
.L2:
        cmpq    $1, %rax    // compare mask with one
        jg      .L3         // if mask > 1 repeat loop
        movq    %rdx, %rax  // move result to %rax
        ret                 // return result
        */

long loop(long a, long b) {
  long result = 0;
  for (long mask = 2; mask > 1; mask <<= b) { //2: movl $2, %eax; update to b because salq %cl, %rax shifts mask left by b bits
    result |= (a & mask); 
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc == 3) {
    long a = strtol(argv[1], NULL, 10);
    long b = strtol(argv[2], NULL, 10);
    printf("loop(%ld, %ld): %ld\n", a, b, loop(a, b));
  } else {
    printf("%ld\n", loop(1, 1)); //0
    printf("%ld\n",loop(3, 2)); //2
    printf("%ld\n",loop(5, 1)); //4
    printf("%ld\n",loop(7, 2)); //2
    printf("%ld\n",loop(9, 1)); //8
  }
  return 0;
}

