#pragma once
#include "UnionFind.h"
#include <unordered_map>

/*
* Basic hashing function used for hashing the pairs for the hashmap
*/
struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

class PercolationSite
{
public:
	PercolationSite(unsigned int size);
	~PercolationSite();
	void openSite(unsigned int row, unsigned int column);
	bool isOpen(unsigned int row, unsigned int column);
	int getTotalOpenSites();
	bool percolates();

private:
	UnionFind* uf;
	std::unordered_map <std::pair<unsigned int, unsigned int>, bool, pair_hash> openSitesMap;
	std::vector<unsigned int> topVerticesFlattened;
	std::vector<unsigned int> bottomVerticesFlattened;
	std::vector<unsigned int> getAllNeighboursFlattened(unsigned int row, unsigned int column);
	unsigned int size;
	unsigned int totalOpenSites;
	bool isFull(unsigned int flattenVertice);
	unsigned int flattenVertice(unsigned int row, unsigned int column);
};

