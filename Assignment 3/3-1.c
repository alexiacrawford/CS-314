#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct IntArray {
    int length;
    int *dataPtr;

};

struct IntArray* mallocIntArray(int length) {
    //allocate memory for IntArray
    struct IntArray* newarray = (struct IntArray*)malloc(sizeof(struct IntArray));
     if (newarray == NULL) {
        printf("IntArray malloc field. \n");
        return NULL;

     }
     newarray->dataPtr = (int*)malloc(length * sizeof(int));
     //allocate memory 
     if (newarray->dataPtr == NULL){
        printf("dataPtr malloc failed. \n");
        return NULL;
     }

    //set length and return pointer 
     newarray->length = length;
     return newarray;
}   


//free allocated memory
void freeIntArray(struct IntArray *arrayPtr){
    free(arrayPtr->dataPtr);
    free(arrayPtr);

}

//read and store integers from user
void readIntArray(struct IntArray *array) {
    char buffer[200]; //should be a big enough size
    char *endptr;
    long value;

    int length;
    do {
        printf("Enter length: "); //asks user for input
        fgets(buffer, sizeof(buffer), stdin);  
        value = strtol(buffer, &endptr, 10); //convert input to long int
        
    } while (value <= 0);

    array->length = (int)value; //set array length

    array->dataPtr = (int*)malloc(array->length * sizeof(int));\
    
    if (array->dataPtr == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);  
    }
    
    for (int i = 0; i < array->length; i++) { // read each integer element into the array
        do {
            printf("Enter int %d: ", i + 1);
            fgets(buffer, sizeof(buffer), stdin); 
            value = strtol(buffer, &endptr, 10);
        } while (value <= 0); 

        array->dataPtr[i] = (int)value;
    }
}

//swap integers using pointers
void swap(int *xp, int *yp) {
    int tempx = *xp; // creates a new variable
    int tempy = *yp;
    *xp = tempy;
    *yp = tempx; // swaps variables
}

void sortIntArray(struct IntArray *array) { // used https://www.geeksforgeeks.org/c-program-for-selection-sort/ as a refrence
    for (int i = 0; i < (array->length) - 1; i++)
    {
        int min_idx = i; //assume first element is min
        for (int j = i + 1; j < array->length; j++)
        {
            if (array->dataPtr[j] < array->dataPtr[min_idx]) //sorts in ascending order
            {
                min_idx = j; //finds smallest element remaining and uptaes min_idx
            }
        }

        if (min_idx != i) {
            swap(&array->dataPtr[min_idx], &array->dataPtr[i]); //swap min element with first unsorted element

        }

    }
}

void printIntArray(struct IntArray *array) {
    printf("[ ");
    for (int i = 0; i < array->length - 1; i++) {
        printf("%d, ", array->dataPtr[i]); //formtting for printing
    }
    printf("%d", array->dataPtr[array->length -1]); //formtting for printing
    printf(" ]\n"); //formtting for printing

}


int main() {
    struct IntArray *array = NULL;
    array = mallocIntArray(0);
    if (array == NULL) {
        printf("allocation failed");
        return 1;
    }

    readIntArray(array); //value of array
    sortIntArray(array);  // ascending order
    printIntArray(array); //print sorted array
    freeIntArray(array); //free memory
    return 0;
}