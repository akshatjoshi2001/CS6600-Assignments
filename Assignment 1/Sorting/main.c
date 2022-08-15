#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sort.c"

#define SEED 5
#define DEBUG 0

void fillArray(long int *array, int size) {

    srand(SEED); // Using a constant seed so that we get the same pseudo-random sequence every time.

    for(int i=0;i<size;i++)
    {
        array[i] = rand()%10000000;
    }

}

void showArray(long int *array, int size) {
    for(int i=0;i<size;i++) {
        printf("%ld ", array[i]);
    }
    printf("\n");
}


int main(int argc,char* argv[]) {
    if(argc < 3) {
        fprintf(stderr, "Please supply all required arguments (sorting method and size of array)\n");
        return -1;
    }

    void (* sort_function) (long int*, int);

    if(strcmp(argv[1],"bubble") == 0) {
        sort_function = bubbleSort;
    }
    else if(strcmp(argv[1],"selection") == 0) {
        sort_function = selectionSort;
    }
    else if(strcmp(argv[1],"radix") == 0) {
        sort_function = radixSort;
    }
    else if(strcmp(argv[1],"merge") == 0) {
        sort_function = mergeSort;
    }
    else if(strcmp(argv[1], "quick") == 0) {
        sort_function = quickSort;
    }
    else {
        fprintf(stderr, "Unknown sort method %s \n", argv[1]);
        return -1;
    }

    short int output_enable = 1;

    if(argc >= 4 && strcmp(argv[3],"disable_output") == 0) {
        output_enable = 0;
    }
    

    int size = atoi(argv[2]);   
    long int* array = malloc(size*sizeof(long int));

    fillArray(array, size);

    if(output_enable == 1) {
        printf("Before Sorting\n");
        showArray(array, size);
    }
   
    
   


    sort_function(array,size);

    if(output_enable == 1) {
        printf("After Sorting\n");
        showArray(array, size);
    }
    

    
  
    


    return 0;


}