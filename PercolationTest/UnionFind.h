#pragma once
#include <vector>

class UnionFind
{
public:
	UnionFind(unsigned int size);
	int findRoot(unsigned int vertex);
	void unionMerge(unsigned int vertex1, unsigned int vertex2);
	bool areConnected(unsigned int vertex1, unsigned int vertex2);

private:
	std::vector<unsigned int> root;
	std::vector<unsigned int> rank;
};

