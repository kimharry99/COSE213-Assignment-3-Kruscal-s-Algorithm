#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 50




/*
* implement the graph as an adjacency list with weight field in a each node
* input : pointer of adjList
* output : pointer of resultAdjList
* V(outputGraph) == V(inputGraph)
* E(outputGraph) ∈ E(inputGraph)
*/


/*
구현을 하고 전역변수를 줄이기
구현 순서 
* TODO : 
inputGraph
printGraph
initializeOutputGraph
KrukalsAlgorithm
edgesort
*DONE :
main
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

nodePointer arrInputAdjList[MAX_ELEMENTS], arrOutputAdjList[MAX_ELEMENTS];
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
	set numbers of elements in arrOutputAdjList equals to arrInputAdjList.
	set links of elements of arrOutputAdjList[] null.	
	save edge data to arrEdge.
	modify arrResultVertexParent
*/
void initializeOutputGraph();
/* sort arrEdge in ascending order by the weight of the edges */
void sortEdge();
/*	add edge to output graph.
	return 1 : adding success, return 0 : adding failure */
int addEdge(edge);
void KrusklsAlgorithm();
void inputGraph();
void printGraph();
/* handle not integer exceptions and out of range exception. */
int goodScanf(int,int);

int main() {
	/*inputGraph();
	initializeOutputGraph();
	sortEdge();
	KrusklsAlgorithm();
	printGraph();
	*/
	return 0;
}

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

void initializeOutputGraph() {

}

void sortEdge() {

}

int addEdge(edge _edge) {

}

void KrusklsAlgorithm() {
	/*	
	while(n(edge)<n(vertex)){
	edge배열에서 하나 꺼내옴
	cycle을 이루는지 검사
	cycle을 이루지 않으면 T에 edge추가
	}
	*/
}

int goodScanf(int rangeA, int rangeB) {
	/* good range = [rangeA, rangeB] */
	int n;
	if (scanf("%d", &n));
	else {
		printf("wrong input.(not an integer)");
		exit(EXIT_FAILURE);
	}
	/* exit program since n is smaller than rangeA */
	if (n<rangeA) {
		printf("Wrong input. (out of range)");
		exit(EXIT_FAILURE);
	}
	else {
		/* exit program since n is bigger than _range */
		if (n > rangeB) {
			printf("Wrong input. (out of range)");
			exit(EXIT_FAILURE);
		}
		else return n;
	}
	printf("Error in the function int goodScanf()");
	exit(EXIT_FAILURE);
}

void inputGraph() {
	int n = 0;
	/*
	* input vertex : number of vertex >> 0~n
	* exceptions :
	*	not integer
	*	out of range (good range = [1,MAX_ELEMENTS])
	*/
	printf("input number of vertex>>");
	if (!scanf("%d", &n)) {

	}


	/*
	* input edges : head and tail and weight 
	* need an end signal (maybe enter -1 at first data)
	* exceptions
	*	input wrong tail 
	*		not integer
	*		out of range(good range = [0,number of vertexes))
	*	input wrong head 
	*		not integer
	*		out of range(good range = [0,number of vertexes))
	*		same with tail
	*		already exsited
	*	input wrong weight
	*		not integer
	*		out of range (good range = [0,∞)) 
	*/

	/* make adjecentList */

	/*	exceptions 
	*		graph is not connected 
	*/
}

void printGraph() {

}
