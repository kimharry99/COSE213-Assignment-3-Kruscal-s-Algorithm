#include <stdio.h>
#define MAX_ELEMENTS 50

/*
* implement the graph as an adjacency list with weight field in a each node
* input : pointer of adjList
* output : pointer of resultAdjList
* V(outputGraph) == V(inputGraph)
*/

/* struct */

typedef struct {
	int head;
	int tail;
	int weight;
}edge ;

typedef struct _node* nodePointer;
typedef struct _node {
	int vertex;
	int weight;
	nodePointer link;
}node;


/* global variables */

nodePointer arrinputAdjList[MAX_ELEMENTS], arrOutputAdjList[MAX_ELEMENTS];
/* use for examining that any cycle is created in the graph. */
int arrResultVertexParent[MAX_ELEMENTS] = { -1, }; 
/* use for ascending sorting of edge weights */
edge arrEdge[MAX_ELEMENTS * (MAX_ELEMENTS - 1)];


/*	union the sets with roots i and j, i!=j, using the weighting rule. 
	arrResultVertexParent[i]-count[i] and arrResultVertexParent[j] =-count[j]	*/
void unionVertexTree(int, int);
/*	find the root that including element i 
	if(findElementRoot(i)==findElementRoot(j)) don't add edge(i,j) to tree T	*/
int findElementRoot(int);
/*	inialize output graph.
	set links of elements of arrOutputAdjList[] null.	*/
void createInitialOutputGraph();
/* sort arrEdge in ascending order by the weight of the edges */
void edgeSort();
/*	add edge to output graph.
	return 1 : adding success, return 0 : adding failure */
int addEdge(edge);
void KrusklsAlgorithm();
void inputGraph();
void printGraph();


void unionVertexTree(int i, int j) 
{	
	int temp = arrResultVertexParent[i] + arrResultVertexParent[j];
	if (arrResultVertexParent[i] > arrResultVertexParent[j]) {
		arrResultVertexParent[i] = j; /* make j the new root */
		arrResultVertexParent[j] = temp;
	}
	else {
		arrResultVertexParent[j] = i; /* make i the new root */
		arrResultVertexParent[i] = temp;
	}
}


int findElementRoot(int i) 
{	
	int root, trail, lead;
	for (root = i; arrResultVertexParent[root] >= 0; root = arrResultVertexParent[root]);
	for (trail = i; trail != root; trail = lead) {
		lead = arrResultVertexParent[trail];
		arrResultVertexParent[trail] = root;
	}
	return root;
}