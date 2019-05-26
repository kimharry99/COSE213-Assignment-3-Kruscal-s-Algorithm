#include <stdio.h>
#define MAX_ELEMENTS 50

/**
* implement the graph as an adjacency list with weight field in a each node
* input : pointer of adjList
* output : pointer of resultAdjList
*/

/**
*사용할 전역 변수 
*vertex의 집합을 구현한 tree의 집합
*
**/
int parent[MAX_ELEMENTS] = { -1, };
void weightedUnion(int, int);
int collaspsingFind(int);


void weightedUnion(int i, int j) 
{	/* union the sets with roots i and j, i!=j, using
	the weighting rule. parent[i]-count[i] and
	parent[j] =-count[j] */
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) {
		parent[i] = j; /* make j the new root */
		parent[j] = temp;
	}
	else {
		parent[j] = i; /* make i the new root */
		parent[i] = temp;
	}
}


//if(find(i)==find(j)) don't add edge(i,j) to tree T;
int collaspsingFind(int i) 
{	/* find the root that including element i */
	int root, trail, lead;
	for (root = i; parent[root] >= 0; root = parent[root]);
	for (trail = i; trail != root; trail = lead) {
		lead = parent[trail];
		parent[trail] = root;
	}
	return root;
}