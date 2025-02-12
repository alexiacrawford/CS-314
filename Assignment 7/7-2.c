#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define SIZE 2048

struct ColorPoint {
    long a;
    long r;
    long g;
    long b;
};

void f(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[i][j].a;
            sum += points[i][j].r;
            sum += points[i][j].g;
            sum += points[i][j].b;
        }
    }
    *dest = sum;
}

void g(struct ColorPoint **points, int n, long *dest) {
    long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[j][i].a;
            sum += points[j][i].r;
            sum += points[j][i].g;
            sum += points[j][i].b;
        }
    }
    *dest = sum;
}

struct ColorPoint** create2DArray(int n) 
{
     // Array holds pointer at the beginning of each row
      struct ColorPoint **points =
              (struct ColorPoint **)malloc(n * sizeof(struct ColorPoint *));
       for (int i = 0; i < n; ++i)
       {
           // Array to hold each row
           points[i] =
                   (struct ColorPoint *) malloc(n * sizeof(struct ColorPoint));
           for (int j = 0; j < n; ++j)
           {
                // Init the ColorPoint struct
                 points[i][j].a = rand();
                 points[i][j].r = rand();
                 points[i][j].g = rand();
                 points[i][j].b = rand();
           }
       }
       return points;
}

void free2DArray(struct ColorPoint** points, int n)
{
    for (int i = 0; i < n; ++i)
    {
    free(points[i]);
    }
    free(points);
}


int main() {
    int n = 2048;
    struct ColorPoint** points = create2DArray(n);

    clock_t start, end;
    double cpu_time_used;

    // Measure time for f
    start = clock();
    for (int i = 0; i < 100; ++i) {
        long result;
        f(points, n, &result);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by f: %f seconds\n", cpu_time_used);

    // Measure time for g
    start = clock();
    for (int i = 0; i < 100; ++i) {
        long result;
        g(points, n, &result);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by g: %f seconds\n", cpu_time_used);

    free2DArray(points, n);

    return 0;
}

/*
void f:
points[0][0].a: Address 0, Cache Miss, cache is  empty.
points[0][0].r: Address 8, Cache Hit, same cache block.
points[0][0].g: Address 16, Cache Hit, same cache block.
points[0][0].b: Address 24, Cache Hit, same cache block.
points[0][1].a: Address 32, Cache Hit, still within the 64B cache block.
points[0][1].r: Address 40, Cache Hit, same cache block.
points[0][1].g: Address 48, Cache Hit, same cache block.
points[0][1].b: Address 56, Cache Hit, same cache block.

This pattern will continue within a row because row-major order makes sure that elements 
in the same row are accessed in an order, so hits will continue for all accesses within the same 
cache block or adjacent blocks. When moving to a new row it will cause a miss because it maps to a new block.
*/

/*
void g:
Cache Analysis: The first access (points[0][0].a) is a cache miss because the cache is empty. Subsequent accesses in the same 
column (e.g., points[1][0].a, points[2][0].a) are also cache misses because they map to different cache blocks.Memory Addresses for 
the first 8 accesses: 
1. points[0][0].a: Address 0, Tag 0, Cache Miss, cache is initially empty.
2. points[1][0].a: Address 128, Tag 2, Cache Miss, different row, new cache block.
3. points[2][0].a: Address 256, Tag 4, Cache Miss, different row, new cache block.
4. points[3][0].a: Address 384, Tag 6, Cache Miss, different row, new cache block.
5. points[0][0].r: Address 8, Tag 0, Cache Miss, different offset, new cache block.
6. points[1][0].r: Address 136, Tag 2, Cache Miss, different row, new cache block.
7. points[2][0].r: Address 264, Tag 4, Cache Miss, different row, new cache block.
8. points[3][0].r: Address 392, Tag 6, Cache Miss, different row, new cache block.

Every memory read is a cache miss because column-major order causes the program to access rows far 
apart in memory, each mapping to a different cache block
*/

/*
main:
f is faster than g. 
f uses row-major order and exploits spatial locality, leading to fewer cache misses and better performance.
g uses column-major order and has poor spatial locality, leading to more cache misses and slower performance
*/