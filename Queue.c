/*
	Implementation of a Queue using a Circular buffer
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t head, tail;
	size_t length, capacity;
	int *arr;
} Queue;

Queue queue_create() {
	Queue q = {0, 0, 0, 1, malloc(sizeof *q.arr)};
	if(q.arr == NULL) fprintf(stderr, "queue_create failed: malloc"), exit(1);
	return q;
}
void queue_destroy(Queue *q) {
	free(q->arr);
}
void queue_resize(Queue *q, size_t capacity) {
	int *arr = malloc(capacity * sizeof *q->arr);
	if(arr == NULL) fprintf(stderr, "queue_resize failed: malloc"), exit(1);

	for(size_t i = 0; i < q->length; i++) arr[i] = q->arr[(q->head + i) % q->capacity];
	free(q->arr);
	q->arr = arr;

	q->capacity = capacity;
	q->head = 0;
	q->tail = q->length;
}
void queue_print(Queue *q) {
	printf("{%d/%d} ", q->length, q->capacity);
	for(size_t i = 0; i < q->capacity; i++)
		printf("%c%d%c", i == q->head ? '[' : ' ', q->arr[i], i == q->tail ? ']' : ' ');
	printf("\n");
}

void queue_push(Queue *q, int value) {
	if(q->length == q->capacity) queue_resize(q, q->capacity * 2);
	q->length++;

	q->arr[q->tail] = value;
	q->tail = (q->tail + 1) % q->capacity;
}
int queue_pop(Queue *q) {
	if(q->length == 0) fprintf(stderr, "queue_pop failed: length == 0"), exit(1);
	if(q->length < q->capacity / 4) queue_resize(q, q->capacity / 2);
	q->length--;

	int value = q->arr[q->head];
	q->head = (q->head + 1) % q->capacity;
	return value;
}



int main() {
	Queue q = queue_create();

	queue_print(&q);                    // {0/1} [6695704]
	queue_push(&q, 1); queue_print(&q); // {1/1} [1]
	queue_push(&q, 2); queue_print(&q); // {2/2} [1] 2 
	queue_push(&q, 3); queue_print(&q); // {3/4} [1  2  3  2138996092]
	queue_push(&q, 4); queue_print(&q); // {4/4} [1] 2  3  4 
	queue_push(&q, 5); queue_print(&q); // {5/8} [1  2  3  4  5  -1616994916] -1549622880  -1482250844 
	printf("\n");
	printf("pop %d\n", queue_pop(&q));  // pop 1
	printf("pop %d\n", queue_pop(&q));  // pop 2
	printf("pop %d\n", queue_pop(&q));  // pop 3
	printf("pop %d\n", queue_pop(&q));  // pop 4
	printf("pop %d\n", queue_pop(&q));  // pop 5

	queue_destroy(&q);
	return 0;
}