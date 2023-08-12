#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BST_node {
	int value;
	struct BST_node *left, *right;
} BST_node;
BST_node *BST_node_create(int value) {
	BST_node *new = malloc(sizeof *new);
	// printf("MALLOC %d, %p\n", value, new);

	if(new == NULL) fprintf(stderr, "BST_node_create failed: malloc"), exit(1);
	*new = (BST_node){value, NULL, NULL};
	return new;
}
void BST_destroy(BST_node *root) {
	if(root == NULL) return;
	BST_destroy(root->left);
	BST_destroy(root->right);

	// printf("FREE %d, %p\n", root->value, root);
	free(root);
}



#define TABS() for(int i = 0; i < level; i++) printf("    ");
void BST_print(BST_node *root, int level) {
	if(root == NULL) {
		printf("x\n");
		return;
	}

	printf("%d\n", root->value);
	if(!root->left && !root->right) return;

	TABS(); printf("Left: ");
	BST_print(root->left, level + 1);

	TABS(); printf("Right: ");
	BST_print(root->right, level + 1);
}
void BST_traversal(BST_node *root) {
	if(root == NULL) return;
	BST_traversal(root->left);
	printf("%d ", root->value);
	BST_traversal(root->right);
}



void BST_insert(BST_node **root, int value) {
	if(*root == NULL) *root = BST_node_create(value);
	else if(value < (*root)->value) BST_insert(&(*root)->left, value);
	else if(value > (*root)->value) BST_insert(&(*root)->right, value);
}
bool BST_search(BST_node *root, int value) {
	if(root == NULL) return false;
	if(root->value == value) return true;
	return BST_search(value < root->value ? root->left : root->right, value);
}



int BST_max(BST_node *root) {return root->right ? BST_max(root->right) : root->value;}
void BST_remove(BST_node **root, int value) {
	if(*root == NULL) return;

	if(value < (*root)->value) BST_remove(&(*root)->left, value);
	else if(value > (*root)->value) BST_remove(&(*root)->right, value);
	else {
		if((*root)->left == NULL || (*root)->right == NULL) {
			BST_node *next = (*root)->left ? (*root)->left : (*root)->right;

			//printf("FREE %d, %p\n", value, *root);
			free(*root);

			*root = next;
		} else {
			(*root)->value = BST_max((*root)->left);
			BST_remove(&(*root)->left, (*root)->value);
		}
	}
}



int main() {
	BST_node *BST = NULL;

	int arr[] = {2, 23, 18, 14, 17, 5, 7, 3, 22, 1, 21, 15, 11, 10, 19, 6, 16, 0, 8, 4, 24, 9, 20, 13, 12};
	for(size_t i = 0; i < 25; i++) BST_insert(&BST, arr[i]);

	BST_print(BST, 0);
	BST_traversal(BST);

	BST_destroy(BST);
	return 0;
}