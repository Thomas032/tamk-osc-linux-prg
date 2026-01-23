#include "stdio.h"
#include "stdlib.h"

int main(void){
    int* array = NULL;
    int size = 10;

    array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for(int i = 0; i < size; i++){
        array[i] = i + 1;
    }

    for(int i = 0; i < size; i++){
        printf("array[%d] = %d\n", i, array[i]);
    }

    free(array);
    return 0;
}