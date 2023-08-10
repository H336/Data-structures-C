#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

typedef struct {
	size_t length;
	size_t capacity;
	int *arr;
} Heap;

Heap heap_create() {
	Heap h = {0, 1, malloc(sizeof *h.arr)};
	if(h.arr == NULL) fprintf(stderr, "heap_create failed: malloc"), exit(1);
	return h;
}
void heap_destroy(Heap *h) {
	free(h->arr);
}
void heap_resize(Heap *h, size_t capacity) {
	h->capacity = capacity;
	h->arr = realloc(h->arr, capacity * sizeof *h->arr);
	if(h->arr == NULL) fprintf(stderr, "heap_resize failed: realloc"), exit(1);
}
void heap_print(Heap *h) {
	printf("[%d / %d] ", h->length, h->capacity);
	for(size_t i = 0; i < h->length; i++) printf("%d ", h->arr[i]);
	printf("\n");
}

void heap_push(Heap *h, int value) {
	if(h->length == h->capacity) heap_resize(h, h->capacity * 2);
	h->arr[h->length++] = value;

	// Up
	size_t i = h->length - 1;
	while(i != 0 && h->arr[i] > h->arr[(i - 1) / 2]) {
		swap(&h->arr[i], &h->arr[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}
int heap_pop(Heap *h) {
	if(h->length == 0) fprintf(stderr, "heap_pop failed: length == 0"), exit(1);
	if(h->length < h->capacity / 4) heap_resize(h, h->capacity / 2);

	int value = h->arr[0];
	h->arr[0] = h->arr[--h->length];

	// Down (heapify)
	size_t i = 0;
	while(2*i + 1 < h->length) {
		int max = 2*i + 1;
		if(max+1 < h->length && h->arr[max+1] > h->arr[max]) max++;
		if(h->arr[i] >= h->arr[max]) break;

		swap(&h->arr[i], &h->arr[max]);
		i = max;
	}

	return value;
}



int main() {
	Heap h = heap_create();

	heap_push(&h, 10);heap_print(&h);  //  [1 / 1] 10
	heap_push(&h, 48);heap_print(&h);  //  [2 / 2] 48 10
	heap_push(&h, 100);heap_print(&h); //  [3 / 4] 100 10 48
	heap_push(&h, 56);heap_print(&h);  //  [4 / 4] 100 56 48 10
	printf("\n");
	printf("pop %d\n", heap_pop(&h));  //  pop 100
	printf("pop %d\n", heap_pop(&h));  //  pop 56
	printf("pop %d\n", heap_pop(&h));  //  pop 48
	printf("pop %d\n", heap_pop(&h));  //  pop 10

	heap_destroy(&h);
	return 0;
}