#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t length;
	size_t capacity;
	int *arr;
} Array;

Array array_create(size_t capacity, int value) {
	Array arr = {capacity, capacity == 0 ? 1 : capacity, malloc(capacity * sizeof *arr.arr)};
	if(arr.arr == NULL) fprintf(stderr, "array_create failed: malloc"), exit(1);

	for(size_t i = 0; i < capacity; i++) arr.arr[i] = value;
	return arr;
}
void array_destroy(Array *arr) {
	free(arr->arr);
}
void array_resize(Array *arr, size_t capacity) {
	arr->capacity = capacity;
	arr->arr = realloc(arr->arr, capacity * sizeof *arr->arr);
	if(arr->arr == NULL) fprintf(stderr, "array_resize failed: realloc"), exit(1);
}
void array_print(Array *arr) {
	printf("[%d / %d] \t", arr->length, arr->capacity);
	for(size_t i = 0; i < arr->length; i++) printf("%d ", arr->arr[i]);
	printf("\n");
}

void array_push(Array *arr, int value) {
	// If there is no space left, increase the capacity by 2 times
	if(arr->length == arr->capacity) array_resize(arr, arr->capacity * 2);
	arr->arr[arr->length++] = value;
}
int array_pop(Array *arr) {
	if(arr->length == 0) fprintf(stderr, "array_pop failed: length == 0"), exit(1);

	// If less than 25% is filled, decrease the capacity by 2 times
	if(arr->length < arr->capacity / 4) array_resize(arr, arr->capacity / 2);
	return arr->arr[--arr->length];
}



int main() {
	Array arr = array_create(3, 0); // {0,0,0}   |   array_create(0, 0) == empty array

	array_print(&arr);                      //  [3 / 3] 	0 0 0 
	array_push(&arr, 1); array_print(&arr); //  [4 / 6] 	0 0 0 1 
	array_push(&arr, 2); array_print(&arr); //  [5 / 6] 	0 0 0 1 2 
	array_push(&arr, 3); array_print(&arr); //  [6 / 6] 	0 0 0 1 2 3 
	array_push(&arr, 4); array_print(&arr); //  [7 / 12] 	0 0 0 1 2 3 4 
	array_push(&arr, 5); array_print(&arr); //  [8 / 12] 	0 0 0 1 2 3 4 5 
	array_push(&arr, 6); array_print(&arr); //  [9 / 12] 	0 0 0 1 2 3 4 5 6 
	array_push(&arr, 7); array_print(&arr); //  [10 / 12] 	0 0 0 1 2 3 4 5 6 7 
	array_push(&arr, 8); array_print(&arr); //  [11 / 12] 	0 0 0 1 2 3 4 5 6 7 8 
	printf("Pop: %d\n", array_pop(&arr));   //  Pop: 8

	array_destroy(&arr);
	return 0;
}