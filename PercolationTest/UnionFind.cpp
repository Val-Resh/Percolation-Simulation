#include "UnionFind.h"

/*
* Constructor!
*/
UnionFind::UnionFind(unsigned int size) : root(size), rank(size)
{
	for (int i = 0; i < size; i++)
	{
		root[i] = i;
		rank[i] = 1;
	}
}

/*
* Find the root of an vertice.
* Implements path compression to reduce search time the next the same vertice is searched.
* Uses recursion to traverse the tree, once root is found, it updates the parent nodes of all traversed nodes to the root.
*/
int UnionFind::findRoot(unsigned int vertice)
{
	if (vertice == root[vertice])
		return vertice;
	return root[vertice] = findRoot(root[vertice]);
}

/*
* Union merge two vertices if they are not already connected.
* Merge decision is made by rank. The rank is the height of the tree.
* The smaller tree is appended to larger tree to avoid increasing the total size of the tree.
* If both are of equal size, then either tree being merged will result in an increase of 1 in rank.
*/
void UnionFind::unionMerge(unsigned int vertice1, unsigned int vertice2)
{
	int rootOfVertice1 = findRoot(vertice1);
	int rootOfVertice2 = findRoot(vertice2);

	if (rootOfVertice1 != rootOfVertice2)
	{
		if (rank[rootOfVertice1] > rank[rootOfVertice2])
			root[rootOfVertice1] = rootOfVertice2;

		else if (rank[rootOfVertice1] < rank[rootOfVertice2])
			root[rootOfVertice2] = rootOfVertice1;

		else
		{
			root[rootOfVertice1] = rootOfVertice2;
			rank[rootOfVertice2]++;
		}
	}
}

/*
* Returns true if two vertices are directly or indirectly connected, returns false otherwise.
*/
bool UnionFind::areConnected(unsigned int vertice1, unsigned int vertice2)
{
	return findRoot(vertice1) == findRoot(vertice2);
}