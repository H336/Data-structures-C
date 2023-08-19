#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Treap_node {
	int key, priority;
	struct Treap_node *l, *r;
} Treap_node;
Treap_node *Treap_node_create(int key, int priority) {
	Treap_node *new = malloc(sizeof *new);
	// printf("MALLOC %d, %p\n", key, new);

	if(new == NULL) fprintf(stderr, "Treap_node_create failed: malloc"), exit(1);
	*new = (Treap_node){key, priority, NULL, NULL};
	return new;
}

Treap_node *Treap_merge(Treap_node *a, Treap_node *b) {
	if(!a || !b) return a ? a : b;
	if(a->priority > b->priority) {
		a->r = Treap_merge(a->r, b);
		return a;
	} else {
		b->l = Treap_merge(a, b->l);
		return b;
	}
}
void Treap_split(Treap_node *root, int key, Treap_node **a, Treap_node **b) {
	if(!root) {
		*a = *b = NULL;
		return;
	}
	if(root->key < key) {
		Treap_split(root->r, key, &root->r, b);
		*a = root;
	} else {
		Treap_split(root->l, key, a, &root->l);
		*b = root;
	}
}



void Treap_insert(Treap_node **root, int key, int priority) {
	Treap_node *less, *greater;
	Treap_split(*root, key, &less, &greater);
	*root = Treap_merge(Treap_merge(less, Treap_node_create(key, priority)), greater);
}
bool Treap_search(Treap_node *root, int key) { // Could be implemented using standard BST function
	Treap_node *less, *equal, *greater;
	Treap_split(root, key, &less, &greater);
	Treap_split(greater, key + 1, &equal, &greater);

	bool result = equal;
	root = Treap_merge(Treap_merge(less, equal), greater);
	return result;
}
void Treap_remove(Treap_node **root, int key) {
	Treap_node *less, *equal, *greater;
	Treap_split(*root, key, &less, &greater);
	Treap_split(greater, key + 1, &equal, &greater);

	Treap_node *toFree = equal;
	equal = Treap_merge(equal->l, equal->r);

	// printf("FREE %d, %p\n", toFree->key, toFree);
	free(toFree);

	*root = Treap_merge(Treap_merge(less, equal), greater);
}

int Treap_min(Treap_node *root) {
	if(root == NULL) return -1;
	while(root->l) root = root->l;
	return root->key;
}
void Treap_print(Treap_node *root) {
	if(root == NULL) return;
	Treap_print(root->l);
	printf("%d ", root->key); //printf("[%d,%d] ", root->key, root->priority);
	Treap_print(root->r);
}
void Treap_destroy(Treap_node *root) {
	if(root == NULL) return;
	Treap_destroy(root->l);
	Treap_destroy(root->r);

	// printf("FREE %d, %p\n", root->key, root);
	free(root);
}



int main() {
	Treap_node *root = NULL;

	int arr[] = {2, 23, 18, 14, 17, 5, 7, 3, 22, 1, 21, 15, 11, 10, 19, 6, 16, 0, 8, 4, 24, 9, 20, 13, 12};
	for(size_t i = 0; i < 25; i++) Treap_insert(&root, arr[i], rand());

	Treap_print(root);printf("\n");
	// printf("%d\n", Treap_search(root, 8));
	// Treap_remove(&root, 8);
	// printf("%d\n", Treap_search(root, 8));
	// Treap_print(root);printf("\n");

	Treap_destroy(root);
	return 0;
}