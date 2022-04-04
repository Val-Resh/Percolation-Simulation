#include "PercolationSite.h"

/*
* Constructor!
*/
PercolationSite::PercolationSite(unsigned int size)
{
	totalOpenSites = 0;
	this->size = size;
	uf = new UnionFind(this->size*this->size);
	openSitesMap = {};

	for (int i = 0; i < size; i++)
	{
		topVerticesFlattened.push_back(flattenVertice(0, i));
		bottomVerticesFlattened.push_back(flattenVertice(size - 1, i));
	}
}

/*
* Destructor!
*/

PercolationSite::~PercolationSite()
{
	delete this->uf;
}

/*
* Opens a site if it is not already open. 
* Add the open sites to the map of open sites and increment the total count by 1.
*/
void PercolationSite::openSite(unsigned int row, unsigned int column)
{
	if (!this->isOpen(row, column))
	{
		std::vector<unsigned int> flattenedNeighbourVertices = getAllNeighboursFlattened(row, column);
		auto vertice = flattenVertice(row, column);

		for (auto verticeToMerge : flattenedNeighbourVertices)
		{
			this->uf->unionMerge(vertice, verticeToMerge);
		}

		this->openSitesMap[std::make_pair(row, column)] = true;
		this->totalOpenSites++;
	}
}

/*
* Returns true if a site is already open, false otherwise.
*/
bool PercolationSite::isOpen(unsigned int row, unsigned int column)
{
	return (openSitesMap.find(std::make_pair(row,column)) != openSitesMap.end());
}

/*
* Checks whether percolation occurs. Returns true if so, false otherwise.
* Percolation occurs when any of the top vertices connect to the bottom through an indirect link of open sites.
*/
bool PercolationSite::percolates()
{
	for (auto bottomVertice : bottomVerticesFlattened)
	{
		if (isFull(bottomVertice))
			return true;
	}
	return false;
}

/*
* Returns the total number of open sites.
*/
int PercolationSite::getTotalOpenSites()
{
	return this->totalOpenSites;
}

/*
* Returns true if a site is full, false otherwise.
* A site is considered full, when it can be connected to the top of the grid via its neighbouring cells. 
* Neighbouring cells are only up, down, right, left. Diagonal cells are not considered neighbours.
*/
bool PercolationSite::isFull(unsigned int flattenedVertice)
{
	
	for (auto topVertice : topVerticesFlattened)
	{
		if (this->uf->areConnected(flattenedVertice, topVertice))
			return true;
	}

	return false;
}

/*
* Flattens the vertice into a 1D coordinate.
*/
unsigned int PercolationSite::flattenVertice(unsigned int row, unsigned int column)
{
	return this->size * row + column;
}

/*
* Return an array with all the neighbours of a given cell as flattened vertices.
*/
std::vector<unsigned int> PercolationSite::getAllNeighboursFlattened(unsigned int row, unsigned int column)
{
	std::vector<unsigned int> flattenedNeighbourVertices;

	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = column - 1; j <= column + 1; j++)
		{
			if ((i == row || j == column) && !(i == row && j == column))
			{
				if (i >= 0 && j >= 0 && i < this->size && j < this->size)
				{
					if (this->isOpen(i, j))
						flattenedNeighbourVertices.push_back(flattenVertice(i, j));
				}
			}
		}
	}

	return flattenedNeighbourVertices;
}