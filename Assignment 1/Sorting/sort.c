#include <limits.h>
#include <math.h>
#define MAX_DIGITS 18

void swap(long int *num1, long int *num2) {
    long int temp = *num2;
    *num2 = *num1;
    *num1 = temp;
}

void bubbleSort(long int *array, int size) {
    short unsigned int swapped = 1;
    while(swapped == 1) {
        // Keep looping until atleast one pair was swapped
        swapped = 0;
        for(int i=0;i<(size-1);i++)
        {
            if(array[i]>array[i+1]){
                // swap neighbouring elements which are not in order               
                swap(&array[i],&array[i+1]);
                swapped = 1;
            }

        }
    }   
}

void quickSortHelper(long int* array, int start, int end) {
    if(start >= end)
        return;
    
    // Use middle element (median) as pivot and send it to the end of the subarray
    int middle = start + ((end-start)>>1);    
    swap(&array[middle], &array[end]); 

    int pivot_final_location = start;

    // Find location of the pivot in the sorted version of the subarray, 
    // and place elements less than pivot before it and remaining after it
    for(int i=start;i<end;i++){
        if(array[i] <  array[end]) {
            swap(&array[i], &array[pivot_final_location]);
            pivot_final_location++;
        }
    } 

    // Place the chosen pivot at the correct position
    swap(&array[end], &array[pivot_final_location]); 

    // recursively sort
    quickSortHelper(array, start, pivot_final_location-1);
    quickSortHelper(array, pivot_final_location+1, end);


}


void quickSort(long int *array, int size) {  
    quickSortHelper(array, 0, size-1);     
}

void selectionSort(long int *array, int size) {
    
    for(int i=0;i<size;i++)
    {
        // select the min element and place it at the beginning of the subarray array[i..size-1]
        long int min_element = LONG_MAX;
        long int min_element_index = -1;
        for(int j=i;j<size;j++)
        {
            if(array[j] < min_element) {
                min_element = array[j];
                min_element_index = j;
               
            }

        }
        swap(&array[i],&array[min_element_index]);
        
    }

}

void mergeSortHelper(long int* array, int start,int end) {
    if(start >= end)
        return;
    int middle = start+((end-start)>>1);

    printf("%d %d", start, end);

    // recursively sort sub-arrays
    mergeSortHelper(array, start, middle);
    mergeSortHelper(array, middle+1, end);


    int i = start;
    int j = middle+1;
    int current = 0;

    // temporary working array for performing merge
    long int* new_array = malloc((end-start+1)*sizeof(long int));

    // performing merge of two halfs
    while(i <= middle && j<=end) {
        if(array[i] <  array[j]) {
            new_array[current] = array[i];
            i++;
        }
        else{
            new_array[current] = array[j];
            j++;
        }
        current++;
    }

    while(i <= middle) {
        new_array[current] = array[i];
        current++;
        i++;
    }

    while(j <= end) {
        new_array[current] = array[j];
        current++;
        j++;
    }

    current = 0;

    // copy from temporary array to actual array.
    for(int k=start;k<=end;k++){
        array[k] = new_array[current];
        current++;
    }

    // free the temporary array memory
    free(new_array);

}

void mergeSort(long int *array, int size) {

    mergeSortHelper(array,0,size-1);

}

void radixSort(long int *array, int size) {  

   for(int position=0;position<MAX_DIGITS;position++) {    
        // running counting sort with key as digit at position 'position' from the right
        int count[10]= {0};       
        long int* temp_array = malloc(sizeof(long int)*size);    

        for(int i=0;i<size;i++) {
            int digit = (array[i]/((int)pow(10,position)))%10;
            
            count[digit]++;
        }

        for(int i=1;i<10;i++) {
            count[i] += count[i-1];
        }

        for(int i=size-1;i>=0;i--) {
            int digit = (array[i]/((int)pow(10,position)))%10;
            temp_array[count[digit]-1] = array[i];
            count[digit]--;
        }

        
        for(int i=0;i<size;i++) {
            array[i] = temp_array[i];
        }

        free(temp_array);
    }

} 



