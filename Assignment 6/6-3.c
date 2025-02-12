#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void f(float *a, int length, float *dest) {
  float prod = 1.0f;
  for (int i = 0; i < length; ++i) {
    if (a[i] != 0.0f) {
      prod *= a[i];
    }
  }
  *dest = prod;
}

void g(float *a, int length, float *dest) {
    float prod = 1.0f;
    for (int i = 0; i < length; ++i) {
        prod *= a[i]; // No zero check
    }
    *dest = prod;
}


float *createArray(int length) {
  float *a = (float *)malloc(length * sizeof(float));
  for (int i = 0; i < length; ++i) {
    // 50% chance that a[i] is 0.0f, random value on the range
    // [0.75, 1.25] otherwise.
    float r = rand()/(float)RAND_MAX;
    a[i] = r < 0.5f ? 0.0f : r + 0.26f;
  }
  return a;
}

int main() {
    int length = 10000; // Array length
    float *a = createArray(length); // Create array a
    float result; // store the result
    clock_t start, end;

    // run time of f(a)
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        f(a, length, &result);
    }
    end = clock();
    printf("f(a): %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // make array b with 0.0f replaced by 1.0f
    float *b = (float *)malloc(length * sizeof(float));
    for (int i = 0; i < length; ++i) {
        b[i] = (a[i] == 0.0f) ? 1.0f : a[i]; // Replace zeros with 1.0f
    }

    // run time of g(b)
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        g(b, length, &result);
    }
    end = clock();
    printf("g(b): %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // make array c with only nonzero elements of a
    int nonzero_count = 0;
    for (int i = 0; i < length; ++i) {
        if (a[i] != 0.0f) {
            ++nonzero_count;
        }
    }
    float *c = (float *)malloc(nonzero_count * sizeof(float));
    int index = 0;
    for (int i = 0; i < length; ++i) {
        if (a[i] != 0.0f) {
            c[index++] = a[i];
        }
    }

    //run time of g(c)
    start = clock();
    for (int i = 0; i < 10000; ++i) {
        g(c, nonzero_count, &result);
    }
    end = clock();
    printf("g(c): %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Free allocated memory
    free(a);
    free(b);
    free(c);

    return 0;
}

/*
with -Og:
f(a): 0.452591 seconds
g(b): 0.346693 seconds
g(c): 0.175392 seconds

f(a): 0.455925 seconds
g(b): 0.349170 seconds
g(c): 0.174063 seconds

f(a): 0.439148 seconds
g(b): 0.348083 seconds
g(c): 0.174202 seconds


calling g(c) is more efficeint than calling g(b) because it deals with a smaller array which lessens the
amount of loop iterations. c only has nonzero elements which lessens the workload, and g(b) still has to process
all the elements of b.
*/
