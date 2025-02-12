#include <stdio.h>
#include <stdlib.h>

struct Set {
    unsigned int tag; // Assume tag is at most 32 bits
    unsigned char valid; // valid bit (0 or 1)
};

struct Cache {
    struct Set *sets;
    int numSets;
};

unsigned int getSet(unsigned int address) {
    return (address >> 1) & 0x7; // 2-byte blocks; 8 sets so 3 set bits
}

unsigned int getTag(unsigned int address) {
    return address >> 4; // total of 4 bits for offset and set
}

struct Cache* mallocCache(int numSets) {
    // TODO - malloc a pointer to a struct Cache, malloc a pointer to an array
    // of struct Set instances (array length is numSets).  Also initialize
    // valid to 0 for each struct Set.  Return the struct Cache pointer.

    // Allocate memory for the Cache struct
    struct Cache *cache = malloc(sizeof(struct Cache));
    if (cache == NULL) {
        perror("Failed to allocate memory for Cache");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the array of sets
    cache->sets = malloc(sizeof(struct Set) * numSets);
    if (cache->sets == NULL) {
        perror("Failed to allocate memory for Cache sets");
        free(cache);
        exit(EXIT_FAILURE);
    }

    // Initialize each set's valid bit to 0
    for (int i = 0; i < numSets; i++) {
        cache->sets[i].valid = 0;
    }

    //Set the number of sets
    cache->numSets = numSets;

    return cache;
}

void freeCache(struct Cache *cache) {
    free(cache->sets);
    free(cache);
}

void printSet(struct Set *set, int setIndex) {
    printf("set: %x - tag: %x - valid: %u\n", setIndex, set->tag, set->valid);
}

void printCache(struct Cache *cache) {
    // TODO - print all valid sets in the cache by calling printSet() as
    // appropriate.

    for (int i = 0; i < cache->numSets; i++) {
        // Check if the set is valid
        if (cache->sets[i].valid) {
            // Print the details of the valid set
            printSet(&cache->sets[i], i);
        }
    }
}


void readValue(struct Cache *cache, unsigned int address) {
    // TODO - check the cache for a valid set containing the specified address.
    // If found, indicate a hit. If not found, update the set's tag and valid
    // state and indicate either a cold miss or conflict miss as appropriate.

    // Get the set index and tag from the address
    unsigned int setIndex = getSet(address);
    unsigned int tag = getTag(address);

    // Get the corresponding set
    struct Set *set = &cache->sets[setIndex];

    // Print the set details
    printf("looking for set: %u - tag: %x\n", setIndex, tag);

    // Check if the set is valid and tag matches
    if (set->valid && set->tag == tag) {
        // set with matching tag
        printf("hit!\n");
    } else {
        if (!set->valid) {
            // set is invalid
            printf("cold miss!\n");
        } else {
            // valid set with a mismatched tag
            printf("conflict miss!\n");
        }

        // Update set's tag and mark it as valid
        set->tag = tag;
        set->valid = 1;
    }
}

unsigned int readUnsignedIntFromHex() {
    char buffer[10];
    char *p = NULL;
    unsigned int n;
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        n = strtoul(buffer, &p, 16);
        if (buffer != p) {
            break;
        }
        printf("Invalid input - try again: ");
    }
    return n;
}

int main() {  
    struct Cache *cache = mallocCache(8);

    char buffer[10];
    char c;
    do {
        printf("Enter 'r' for read, 'p' to print, 'q' to quit: ");
        fgets(buffer, sizeof(buffer), stdin);

        c = buffer[0];
        if (c == 'r') {                     
             printf("Enter 32-bit unsigned hex address: ");
             unsigned int a = readUnsignedIntFromHex();
             readValue(cache, a);
        } else if (c == 'p') {
             printCache(cache);
        }
    } while (c != 'q');

    freeCache(cache);
}