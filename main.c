#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 50

/*
* implement the graph as an adjacency list with weight field in a each node
* input : pointer of adjList
* output : pointer of resultAdjList
* V(outputGraph) == V(inputGraph)
* E(outputGraph) ¡ô E(inputGraph)
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

/* 0 : input graph, 1 : output graph */
nodePointer arrAdjList[2][MAX_ELEMENTS] = { NULL, };
/* use for examining that any cycle is created in the graph. */
int arrOutputVertexParent[MAX_ELEMENTS]; 
int arrInputVertexParent[MAX_ELEMENTS];
/* use for ascending sorting of edge weights */
edge arrEdge[MAX_ELEMENTS * (MAX_ELEMENTS - 1)];


/*	union the sets with roots i and j, i!=j, using the weighting rule. 
	arrOutputVertexParent[i]-count[i] and arrOutputVertexParent[j] =-count[j]	*/
void unionVertexTree(int *,int, int);
/*	find the root that including element i 
	if(findElementRoot(i)==findElementRoot(j)) don't add edge(i,j) to tree T	*/
int findElementRoot(int);
/* sort arrEdge in ascending order by the weight of the edges */
void sortEdge(edge arr[], int left, int right);
/*	add edge to graph arrAdjList[x].
	return 1 : adding success, return 0 : adding failure */
int addEdge(edge,int);
void KrusklsAlgorithm();
/*	return edge.head = number of vertex 
	edge.tail = number of edges
	save edge data to arrEdge.
	reset arrOutputVertexParent to -1
*/
edge inputGraph();
void printGraph(nodePointer*,int n);
/* handle not integer exceptions and out of range exception. */
int goodInput(int,int);
/*	param : number of vertex of graph
	return : 1 graph is connect */
int isConnect(int);



int main() {
	edge n = inputGraph();
	printf("\ninput graph is \n\n");
	printGraph(arrAdjList[0], n.head);
	sortEdge(arrEdge, 0, n.tail-1);
	KrusklsAlgorithm();
	printf("\nthe minimum cost spanning tree of this graph is \n\n");
	printGraph(arrAdjList[1], n.head);
	return 0;
}

void unionVertexTree(int* arr, int i, int j) 
{	
	if (i != j) {
		int temp = arrOutputVertexParent[i] + arrOutputVertexParent[j];
		if (arrOutputVertexParent[i] > arrOutputVertexParent[j]) {
			arrOutputVertexParent[i] = j; /* make j the new root */
			arrOutputVertexParent[j] = temp;
		}
		else {
			arrOutputVertexParent[j] = i; /* make i the new root */
			arrOutputVertexParent[i] = temp;
		}
	}
}


int findElementRoot(int i) 
{	
	int root, trail, lead;
	for (root = i; arrOutputVertexParent[root] >= 0; root = arrOutputVertexParent[root]);
	for (trail = i; trail != root; trail = lead) {
		lead = arrOutputVertexParent[trail];
		arrOutputVertexParent[trail] = root;
	}
	return root;
}


void sortEdge(edge arr[], int left, int right) {
	int i = left, j = right;
	  int pivot = arr[(left + right) / 2].weight;
      edge temp;
      do
      {
        while (arr[i].weight < pivot)
            i++;
        while (arr[j].weight > pivot)
            j--;
        if (i<= j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
      } while (i<= j);

    /* recursion */
    if (left < j)
        sortEdge(arr, left, j);

    if (i < right)
        sortEdge(arr, i, right);
}

int addEdge(edge _edge, int x) {
	/*	read the information of _edge and make new node then add to adjcent list */
	nodePointer w,temp;
	if (x == 0 || x == 1) {
		if (arrAdjList[x][_edge.tail] == NULL) {
			temp = (nodePointer)malloc(sizeof(node));
			temp->link = NULL;
			temp->weight = _edge.weight;
			temp->vertex = _edge.head;
			arrAdjList[x][_edge.tail] = temp;
		}
		else {
			for (w = arrAdjList[x][_edge.tail]; w->link != NULL; w = w->link)
				if (w->vertex == _edge.head)
					/* edge is already in the graph */
					return 0;
			if (w->vertex == _edge.head)
					/* edge is already in the graph */
					return 0;
			temp = (nodePointer)malloc(sizeof(node));
			temp->link = NULL;
			temp->weight = _edge.weight;
			temp->vertex = _edge.head;
			w->link = temp;
		}
		if (arrAdjList[x][_edge.head] == NULL) {
			temp = (nodePointer)malloc(sizeof(node));
			temp->link = NULL;
			temp->weight = _edge.weight;
			temp->vertex = _edge.tail;
			arrAdjList[x][_edge.head] = temp;
		}
		else {
			/* search end of the list */
			for (w = arrAdjList[x][_edge.head]; w->link != NULL; w = w->link)
				/* edge is already in the graph */
				if (w->vertex == _edge.tail)
					return 0;
			if (w->vertex == _edge.tail)
					/* edge is already in the graph */
					return 0;
			temp = (nodePointer)malloc(sizeof(node));
			temp->link = NULL;
			temp->weight = _edge.weight;
			temp->vertex = _edge.tail;
			w->link = temp;
		}
	}
	else {
		printf("add Edge error.(wrong parameter x)");
		exit(EXIT_FAILURE);
	}
}

void KrusklsAlgorithm() {
	int nVertex=0;
	int nEdge = 0;
	for (; arrOutputVertexParent[nVertex] == -1; nVertex++);
	for (int i = 0; nEdge < nVertex-1;i++) {
		edge temp;
		temp = arrEdge[i];
		/* added edge don't make cycle */
		int rootHead = findElementRoot(temp.head);
		int rootTail = findElementRoot(temp.tail);
		if (!(rootHead == rootTail)) {
			unionVertexTree(arrOutputVertexParent, rootHead, rootTail);
			addEdge(temp, 1);
			nEdge++;
		}
	}

}

int goodInput(int rangeA, int rangeB) {
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

edge inputGraph() {
	edge returnEdge;
	returnEdge.weight = -1;
	int n = 0;
	/*
	* input vertex : number of vertex >> 0~n
	* exceptions :
	*	not integer
	*	out of range (good range = [1,MAX_ELEMENTS])
	*/
	printf("input number of vertex>>");
	n = goodInput(1, MAX_ELEMENTS);
	returnEdge.head = n;
	printf("\nNumber of vertices in graph : %d\n\n", n);
	for (int i = 0; i < n; i++) {
		arrInputVertexParent[i] = -1;
		arrOutputVertexParent[i] = -1;
	}
	/* Input edge */
	for (int i = 0;; i++) {
		edge temp;
		printf("Input tail of edge	(enter -1 to end input)	>>");
		temp.tail = goodInput(-1, MAX_ELEMENTS);
		if (temp.tail == -1)
			break;
		printf("Input head of edge				>>");
		temp.head = goodInput(0, MAX_ELEMENTS);
		if (temp.head == temp.tail) {
			printf("tail and head is same");
			exit(EXIT_FAILURE);
		}
		printf("Input weight of edge				>>");
		temp.weight = goodInput(0, 10000);
		/* make adjecentList */
		if (!addEdge(temp, 0)) {
			printf("edge is already exist.");
			exit(EXIT_FAILURE);
		}
		unionVertexTree(arrInputVertexParent, temp.head, temp.tail);
		arrEdge[i] = temp;
		returnEdge.tail = i+1;
		printf("edge (%d,%d) weight : %d\n\n", temp.tail, temp.head, temp.weight);
	}
	
	/*	exceptions
	*		graph is not connected
	*/
	if (!isConnect(n)) {
		printf("graph is not connected.");
		exit(EXIT_FAILURE);
	}
	return returnEdge;
}

void printGraph(nodePointer* _adjList,int n) {
	nodePointer w;
	printf("\n");
	for (int i = 0; i < n; i++) {
		if (_adjList[i]) {
				printf("%d -> ",i);
			for (w = _adjList[i]; w; w = w->link) {
				printf("%d|%d ", w->vertex, w->weight);
				if (w->link)
					printf("-> ");
			}
		}
		else
		{
			printf("%d", i);
		}	
		printf("\n");
	}
	printf("\n\n");
}


int isConnect(int n) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (arrInputVertexParent[i] < 0)
			cnt++;
		if (cnt > 1)
			return 0;
	}
	return 1;
}