//  Main program for maze generation program.

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "mazeGenerator.h"

using namespace std;

// *****************************************************************

int main(int argc, char *argv[])
{

// *****************************************************************
//  Declarations, headers...

	string		stars, bars, dashes;
	string		fName;
	const char	*bold = "\033[1m";
	const char	*unbold = "\033[0m";
	bool		doPrint=false;
	int		rows, cols;
	mazeGenerator	myMaze;

	stars.append(65, '*');
	bars.append(65, '=');
	dashes.append(40,'-');

// ------------------------------------------------------------------
//  Get/check arguments

	if (!myMaze.getArguments(argc, argv, rows, cols, fName, doPrint))
		exit(1);

// ------------------------------------------------------------------
//  Create an amazing new maze.  :-)

	if (!myMaze.setSize(rows, cols)) {
		cout << "Error, invalid maze size." << endl;
		exit(1);
	}

	myMaze.generate();

	if (!myMaze.printMazeData(fName)) {
		cout << "Error creating output file: " << fName << "." << endl;
	} else {
		cout << stars << endl << bold << "CS 302 - Assignment #10" << endl;
		cout << "Maze Generator" << unbold << endl;
		cout << endl;

		cout << "Maze file " << fName << " created." << endl;

		if (doPrint) {
			cout << dashes << endl << "Generated Maze:" << endl << endl;
			myMaze.printMazeText();
			cout << endl << dashes << endl;
		}
	}

// *****************************************************************
//  All done.

	cout << endl << "Game Over, thank you for playing." << endl;

	return 0;
}

