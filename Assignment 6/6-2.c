#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inner(float *u, float *v, int length, float *dest) {
  float sum = 0.0f;
  for (int i = 0; i < length; ++i) {
    sum += u[i] * v[i];
  }
  *dest = sum;
}

void inner2(float *u, float *v, int length, float *dest) {
    float sum1 = 0.0f, sum2 = 0.0f, sum3 = 0.0f, sum4 = 0.0f;
    int i;

    // 4 way loop unrolling
    for (i = 0; i <= length - 4; i += 4) {
        sum1 += u[i] * v[i]; //accumulator 1
        sum2 += u[i + 1] * v[i + 1]; //accumulator 2
        sum3 += u[i + 2] * v[i + 2]; //accumulator 3
        sum4 += u[i + 3] * v[i + 3]; //accumulator 4
    }

    //remaining elements
    for (; i < length; i++) {
        sum1 += u[i] * v[i];
    }

    *dest = sum1 + sum2 + sum3 + sum4;
}

void inner3(float *u, float *v, int length, float *dest) {
    float sum1 = 0.0f, sum2 = 0.0f, sum3 = 0.0f, sum4 = 0.0f;
    float sum5 = 0.0f, sum6 = 0.0f, sum7 = 0.0f, sum8 = 0.0f;
    int i;

    // 8 way loop unrolling
    for (i = 0; i <= length - 8; i += 8) {
        sum1 += u[i] * v[i]; //accumulator 1
        sum2 += u[i + 1] * v[i + 1]; //accumulator 2
        sum3 += u[i + 2] * v[i + 2]; //accumulator 3
        sum4 += u[i + 3] * v[i + 3]; //accumulator 4
        sum5 += u[i + 4] * v[i + 4]; //accumulator 5
        sum6 += u[i + 5] * v[i + 5]; //accumulator 6
        sum7 += u[i + 6] * v[i + 6]; //accumulator 7 
        sum8 += u[i + 7] * v[i + 7]; //accumulator 8
    }

    //remaining elements
    for (; i < length; i++) {
        sum1 += u[i] * v[i];
    }

    *dest = sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7 + sum8;
}

float *createArray(int length) {
    float *a = (float *)malloc(length * sizeof(float));
    for (int i = 0; i < length; ++i) {
        a[i] = rand() / (float)RAND_MAX; // Initialize with random float values between 0 and 1
    }
    return a;
}

int main() {
    int length = 100000;
    float *u = createArray(length);
    float *v = createArray(length);
    float result;

    clock_t start, end;

    // Time inner
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        inner(u, v, length, &result);
    }
    end = clock();
    printf("inner: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Time inner2
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        inner2(u, v, length, &result);
    }
    end = clock();
    printf("inner2: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Time inner3
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        inner3(u, v, length, &result);
    }
    end = clock();
    printf("inner3: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Free allocated memory
    free(u);
    free(v);

    return 0;
}

/*when I compile with gcc -Og 6-2.c and then ./a.out, my runtime are as follows:

inner: 0.000007 seconds
inner2: 0.000002 seconds
inner3: 0.000000 seconds

inner: 0.000008 seconds
inner2: 0.000001 seconds
inner3: 0.000001 seconds

inner: 0.000002 seconds
inner2: 0.000000 seconds
inner3: 0.000000 seconds

without -O

inner: 3.485849 seconds
inner2: 0.921266 seconds
inner3: 0.814357 seconds

inner: 3.484850 seconds
inner2: 0.922808 seconds
inner3: 0.804979 seconds

inner: 3.503114 seconds
inner2: 0.920205 seconds
inner3: 0.813122 seconds

Inner3 is the fastest but not the most efficient. It works really well for very large numbers.
Inner2 i the most efficient and simple. there aren't as many loop iterations and has less memory pressure than inner



*/



