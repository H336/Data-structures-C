/*
	Graph implementation using adjacency list (using linked list)
	+ DFS test
*/

#include <stdio.h>
#include <stdlib.h>
/*#include <stdbool.h>
#include <string.h>*/

typedef struct Graph_node {
	int dst;
	struct Graph_node *next;
} Graph_node;
typedef struct {
	int V;
	Graph_node **adj; // Array of Graph_node*
} Graph;
Graph_node *graph_node_create(int dst, Graph_node *next) {
	Graph_node *new = malloc(sizeof(Graph_node));
	// printf("MALLOC %d, %p\n", dst, new);

	if(new == NULL) fprintf(stderr, "graph_node_create failed: malloc"), exit(1);
	new->dst = dst;
	new->next = next;
	return new;
}
Graph graph_create(int V) {
	Graph g = {V, calloc(V, sizeof(Graph_node*))};
	if(g.adj == NULL) fprintf(stderr, "graph_create failed: calloc"), exit(1);
	return g;
}
void graph_destroy(Graph *g) {
	for(size_t i = 0; i < g->V; i++) {
		Graph_node *aux = g->adj[i];
		while(aux) {
			Graph_node *next = aux->next;

			// printf("FREE %d, %p\n", aux->dst, aux);
			free(aux);

			aux = next;
		}
	}
}
void graph_add_edge(Graph *g, int src, int dst) {
	g->adj[src] = graph_node_create(dst, g->adj[src]);
	g->adj[dst] = graph_node_create(src, g->adj[dst]);
}



/*void dfs(Graph *g, bool visited[], int v) {
	visited[v] = true;
	printf("%d ", v);

	Graph_node *aux = g->adj[v];
	while(aux) {
		if(!visited[aux->dst]) dfs(g, visited, aux->dst);
		aux = aux->next;
	}
}*/



int main() {
	int V = 10, E = 11;
	Graph g = graph_create(V);
	int edges[][2] = {{0,1}, {1,8}, {8,5}, {8,2}, {5,6}, {7,3}, {2,6}, {7,9}, {3,9}, {2,4}, {0,8}};
	for(size_t i = 0; i < E; i++) graph_add_edge(&g, edges[i][0], edges[i][1]);

	/*
	printf("Connected components (DFS):\n");
	bool visited[V];
	memset(visited, 0, sizeof visited);

	int n = 0;
	for(int i = 0; i < V; i++) {
		if(!visited[i]) {
			printf("%d.\t", ++n);
			dfs(&g, visited, i);
			printf("\n");
		}
	}



	Output:
		Connected components (DFS):
		1.	0 1 8 2 4 6 5 
		2.	3 9 7 
	*/

	graph_destroy(&g);
	return 0;
}