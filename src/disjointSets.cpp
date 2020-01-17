
#include <iostream>
#include <iomanip>
#include "disjointSets.h"

using namespace std;


// initialize links & ranks to empty state
// check parameter ensure >= MIN_SIZE, if not use default value (10)
disjointSets::disjointSets(int size)
{
	if (size < MIN_SIZE)
		setSize = 10;
	else
		setSize = size;

	currSet = setSize;

	links = new int[setSize]();
	ranks = new int[setSize]();

	for (int i = 0; i < setSize; i ++)
	{
		links[i] = -1;
		ranks[i] = 1;
	}
}


// delete dynamically allocated memory
disjointSets::~disjointSets()
{
	delete []links;
	delete []ranks;
}


// print current disjoint set status, links & ranks, w/ index
void disjointSets::printSets() const
{
	cout << "  " << "index:";

	for (int i = 0; i < setSize; i ++)
		cout << setw(3) << i;

	cout << endl;
	cout << "  " << "links:";

	for (int i = 0; i < setSize; i ++)
		cout << setw(3) << links[i];

	cout << endl;
	cout << "  " << "ranks:";

	for (int i = 0; i < setSize; i ++)
		cout << setw(3) << ranks[i];

	cout << endl;

}


// return current set size
int disjointSets::entries() const
{
	return currSet;
}


// perform union-by-rank operation b/w 2 passed sets & return parent
// passed set numbers must be range checked
int disjointSets::setUnion(int r1, int r2)
{	
	if (r1 > setSize - 1 || r2 > setSize - 1)
		return -1;

	if (r1 < 0 || r2 < 0)
		return -1;

	int parent = 0; 
	int child = 0;

	if (setFind(r1) != -1)
		r1 = setFind(r1);

	if (setFind(r2) != -1)
		r2 = setFind(r2);

	if (ranks[r1] <= ranks[r2])
	{
		parent = r2;
		child = r1;
	}

	else
	{
		parent = r1;
		child = r2;
	}

	links[child] = parent;

	if (ranks[r1] == ranks[r2])
		ranks[parent]++;

	currSet--;
	return parent; 
}


// search parent of passed set, could be set itself
// passed set number must be ranged checked
// perform path compression
int disjointSets::setFind(int search)
{	
	if (search > setSize - 1)
		return -1;

	if (search < 0)
		return -1;

	if (links[search] < 0)
		return search;

	else
		return links[search] = setFind(links[search]);
}