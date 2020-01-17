//  Main program for testing

#include <iostream>
#include <string>
#include <cstdlib>

#include "disjointSets.h"

using namespace std;

int main(int argc, char *argv[])
{

// *****************************************************************
//  Headers...

	string	stars, bars, dashes;
	stars.append(65, '*');
	bars.append(65, '=');
	dashes.append(40,'-');
	const char* bold   = "\033[1m";
	const char* unbold   = "\033[0m";

	cout << stars << endl << bold << "CS 302 - Assignment #9" << endl;
	cout << "Disjoint Sets" << unbold << endl;
	cout << endl;

// ------------------------------------------------------------------
//  Basic testing for disjoint sets data structure...

	disjointSets	setTest0(10);
	int	m01, m23, m45;
	int	m0123, m456, m4567, m45678;
	int	m012345678;

	cout << "Initial State:" << endl;
	setTest0.printSets();
	cout << endl;

	cout << dashes << endl;
	m01 = setTest0.setUnion(0, 1);
	cout << "  union(0,1) -> " << m01 << endl;
	m23 = setTest0.setUnion(2, 3);
	cout << "  union(2,3) -> " << m23 << endl;
	m45 = setTest0.setUnion(4, 5);
	cout << "  union(4,5) -> " << m45 << endl;

	cout << endl << "New State 1:" << endl;
	setTest0.printSets();
	cout << endl;

	cout << dashes << endl;
	m0123 = setTest0.setUnion(m01, m23);
	cout << "  union(" << m01 << "," << m23 << ") -> " << m0123 << endl;
	m456 = setTest0.setUnion(m45, 6);
	cout << "  union(" << m45 << ",6" << ") -> " << m456 << endl;
	m4567 = setTest0.setUnion(m456, 7);
	cout << "  union(" << m456 << ",7" << ") -> " << m4567 << endl;
	m45678 = setTest0.setUnion(m4567, 8);
	cout << "  union(" << m4567 << ",8" << ") -> " << m45678 << endl;

	cout << endl << "New State 2:" << endl;
	setTest0.printSets();
	cout << endl;

	cout << dashes << endl;
	cout << "  setFind(1): " << setTest0.setFind(1) << endl;
	cout << "  setFind(2): " << setTest0.setFind(2) << endl;
	cout << "  setFind(4): " << setTest0.setFind(4) << endl;
	cout << "  setFind(7): " << setTest0.setFind(7) << endl;

	cout << endl << "New State 3:" << endl;
	setTest0.printSets();
	cout << endl;

	cout << dashes << endl;
	m012345678 = setTest0.setUnion(m0123, m45678);
	cout << "m0123 = " << m0123 << endl;
	cout << "m45678 = " << m45678 << endl;
	cout << "  union(m0123,m45678) -> " << m012345678 << endl;

	cout << endl << "New State 4:" << endl;
	setTest0.printSets();
	cout << endl;

	cout << dashes << endl;
	cout << "  setFind(3): " << setTest0.setFind(3) << endl;
	cout << "  setFind(5): " << setTest0.setFind(5) << endl;
	cout << "  setFind(7): " << setTest0.setFind(7) << endl;

	cout << endl << "New State 5:" << endl;
	setTest0.printSets();
	cout << endl;

	cout << dashes << endl;
	cout << "  setFind(0): " << setTest0.setFind(0) << endl;

	cout << endl << "New State 6:" << endl;
	setTest0.printSets();
	cout << endl;

	cout << dashes << endl;
	cout << "  setFind(4): " << setTest0.setFind(4) << endl;
	cout << "  setFind(6): " << setTest0.setFind(6) << endl;
	cout << "  setFind(8): " << setTest0.setFind(8) << endl;

	cout << endl << "Final State:" << endl;
	setTest0.printSets();
	cout << endl;

// ------------------------------
//  Misc error testing

	{
		disjointSets	setTest1(10000);
		if (setTest1.entries() != 10000)
			cout << "Test Set 1, size error." << endl;
	}

	disjointSets	setTest2(9);
	if (setTest2.entries() != 10)
		cout << "Test Set 2, size error." << endl;

	disjointSets	setTest3;
	if (setTest3.entries() != 10)
		cout << "Test Set 3, size error." << endl;

	for (int i=0; i<10; i++)
		if (setTest3.setFind(i) != i)
			cout << "Test Set 3, find error." << endl;

	if (setTest3.setFind(11) != -1)
		cout << "Test Set 3, set find range checking error." << endl;
	if (setTest3.setFind(-5) != -1)
		cout << "Test Set 3, set find range checking error." << endl;
	if (setTest3.setUnion(11,12) != -1)
		cout << "Test Set 3, set union range checking error." << endl;
	if (setTest3.setUnion(-2,-2) != -1)
		cout << "Test Set 3, set union range checking error." << endl;



// *****************************************************************
//  All done.

	cout << endl << stars << endl <<
		"Game Over, thank you for playing." << endl;

	return 0;
}

