
// mazeGenerator Functions

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "disjointSets.h"
#include "mazeGenerator.h"

using namespace std;


// initialize class variables as appropriate
mazeGenerator::mazeGenerator()
{
	rows = 0; 
	cols = 0;
	walls = NULL;
}


// delete dynamically allocated memory
mazeGenerator::~mazeGenerator()
{
	int wCount = ((cols - 1) * rows) + (rows - 1) * cols;

	for (int i = 0; i < wCount; i ++)
		delete[] walls[i];

	delete[] walls;
}


// set curr maze size, rows & cols in order of curr maze size
// ensure both >= (MIN_ROWS & MIN_COLS) & <= (MAX_ROWS & MAX_COLS)
// if not, return false
// if valid, multi-dimension walls array is created and initialized
bool mazeGenerator::setSize(int argRows, int argCols)
{
	if (argRows > MAX_ROWS || argRows < MIN_ROWS || argCols > MAX_COLS || argCols < MIN_COLS)
		return false;

	rows = argRows;
	cols = argCols;

	int wCount = ((cols - 1) * rows) + (rows - 1) * cols;

	walls = new int*[wCount];

	for (int i = 0; i < wCount; i ++)
		walls[i] = new int[2];

	for (int i = 0; i < wCount; i ++)
		for (int j = 0; j < 2; j ++)
			walls[i][j] = -1;

	return true; 
}


// print maze data to file starting w/ size (ROWS r COLS c)
// then data about where wall is located
// if file is created, function return true
// false otherwise
bool mazeGenerator::printMazeData(const string fName) const
{
	ofstream outFile;
	outFile.open(fName.c_str());

	if (!outFile.is_open())
		return false;

	int wCount = ((cols - 1) * rows) + (rows - 1) * cols;

	outFile << "ROWS " << rows << " COLS " << cols << endl;

	for (int i = 0; i < wCount; i ++)
	{
		if(walls[i][0] != -1)
			outFile << "WALL " << walls[i][0] << " " << walls[i][1] << endl;
	}

	return true;
}


// accept & validate command line arguments
// "./maze -r <rows> -c <columns> -o <fileName> [-p]"
// "./maze -o <fileName> [-p] -c <cols> -r <rows>"
// -r = # of rows (int)
// -c = # of columns (int)
// -o = output file name (string)
// -p = if maze displayed (bool)
// check validity of numeric values (if it's # instead of string, etc), not range
bool mazeGenerator::getArguments(int c, char *v[], int& argRows, int& argCols, string& fName, bool& doPrint)
{
	if (c == 1)
	{
		cout << "Usage: ./maze -r <rows> -c <columns> -o <fileName> [-p]" << endl;
		return false;
	}

	if (c != 8 && c != 7)				
	{
		cout << "Error, command line arguments are invalid." <<endl;
		return false;
	}

	bool r = false;				
	int rIndex = 0;			

	bool col = false;
	int colIndex = 0;

	bool o = false;
	int oIndex = 0;

	bool p = false;

	stringstream mySS;
	stringstream mySS2;
	string errorMsg = "";

	if (c == 7)
	{
		for (int i = 1; i < c; i++)
		{

			if (string(v[i]) == "-r")
			{
				if (r == true)				// appear twice
				{
					r = false;
					errorMsg = "Error, invalid rows specifier.";
				}

				else
				{
					r = true;				// appear once
					rIndex = i;				// get index
				}
			}

			else if (string(v[i]) == "-c")
			{	
				if (col == true)				// appear twice
				{
					col = false;
					errorMsg = "Error, invalid columns specifier.";
				}

				else
				{
					col = true;				// appear once
					colIndex = i;				// get index 
				}		
			}

			else if (string(v[i]) == "-o")
			{	
				if (o == true)				// appear twice
				{
					o = false;
					errorMsg = "Error, output file specifier.";
				}

				else
				{
					o = true;				// appear once
					oIndex = i;				// get index 
				}		
			}
		}
	}

	else if (c == 8)
	{
		for (int i = 1; i < c; i++)
		{
			if (string(v[i]) == "-r")
			{
				if (r == true)				// appear twice
				{
					r = false;
					errorMsg = "Error, invalid rows specifier.";
				}

				else
				{
					r = true;				// appear once
					rIndex = i;				// get index
				}
			}

			else if (string(v[i]) == "-c")
			{	
				if (col == true)				// appear twice
				{
					col = false;
					errorMsg = "Error, invalid columns specifier.";
				}

				else
				{
					col = true;				// appear once
					colIndex = i;				// get index 
				}		
			}

			else if (string(v[i]) == "-o")
			{	
				if (o == true)				// appear twice
				{
					o = false;
					errorMsg = "Error, output file specifier.";
				}

				else
				{
					o = true;				// appear once
					oIndex = i;				// get index 
				}		
			}

			else if (string(v[i]) == "-p")
			{
				if (p == true)
				{
					p = false;
					errorMsg = "Error, invalid print specifier.";
				}

				else
					p = true;
			}
		}
	}
		
	if(c == 7)
	{
		if (!r || !col || !o)
		{	
			if (errorMsg == "")				// arguments never existed
			{
				if (!r)
					errorMsg = "Error, invalid rows specifier.";

				else if (!col)
					errorMsg = "Error, invalid columns specifier.";

				else if (!o)
					errorMsg = "Error, invalid output file specifier.";
			}

			cout << errorMsg << endl;
			return false;
		}
	}

	else if(c == 8)
	{
		if (!r || !col || !o || !p)
		{	
			if (errorMsg == "")				// arguments never existed
			{
				if (!r)
					errorMsg = "Error, invalid rows specifier.";

				else if (!col)
					errorMsg = "Error, invalid columns specifier.";

				else if (!o)
					errorMsg = "Error, invalid output file specifier.";

				else if (!p)
					errorMsg = "Error, invalid print specifier.";
			}

			cout << errorMsg << endl;
			return false;
		}
	}

	if (r)
	{
		if (string(v[rIndex + 1]) != "")
		{
			mySS << v[rIndex + 1];
			mySS >> argRows;

			if (mySS.fail() || !mySS.eof())
			{
				errorMsg = "Error, invalid rows value.";
				cout << errorMsg << endl;
				return false;
			}
		}
	}

	if (col)
	{
		if (string(v[colIndex + 1]) != "")
		{
			mySS2 << v[colIndex + 1];
			mySS2 >> argCols;

			if (mySS2.fail() || !mySS2.eof())
			{
				errorMsg = "Error, invalid columns value.";
				cout << errorMsg << endl;
				return false;
			}
		}
	}

	if(o)
	{
		ofstream outFile;
		fName = string(v[oIndex + 1]);
		outFile.open(fName.c_str());

		if (!outFile.is_open())
		{
			errorMsg = "Error, unable to open output file.";
			cout << errorMsg << endl;
			outFile.close();
			return false;
		}

		outFile.close();
	}

	if (p)
		doPrint = true;
	
	else
		doPrint = false;

 	return true; 
}


// return curr maze size, rows & cols in order of curr maze size
void mazeGenerator::getSize(int& argRows, int& argCols) const
{	
	argRows = rows;
	argCols = cols;
}


// generate a new maze based on disjoint sets method
void mazeGenerator::generate()
{
	int wCount = ((cols - 1) * rows) + (rows - 1) * cols;


	// GENERATING ALL THE INTERIOR WALLS

	int cell0 = 0;
	int cell1 = 1; 
	int vertDone = 0; 

	for (int i = 0; i < wCount; i ++)			// vertical walls
	{
		if ((cell0 < rows * cols) && (cell1 < rows * cols))
		{
			if (((cell0 + 1) % cols) == 0)		// row ends
			{
				cell0 ++;
				cell1 ++;
			}

			walls[i][0] = cell0;				// insert normally
			walls[i][1] = cell1;
			cell0 ++;
			cell1 ++;
		}

		else
		{
			vertDone = i;
			break;
		}
	}

	cell0 = 0;
	cell1 = cols;

	for (int i = vertDone; i < wCount; i ++)	// horizontal wall
	{
		if ((cell0 < rows * cols) && (cell1 < rows * cols))
		{
			walls[i][0] = cell0;				// insert normally
			walls[i][1] = cell1;
			cell0 ++;
			cell1 ++;
		}
	}


	// RANDOMIZING AND CREATING SETS 

	randomize(); 
	disjointSets wSet(rows * cols);
	int idx = 0;

	while (wSet.entries() != 1)								// when entries = 1, theres 1 set 
	{														// which means the maze has 1 solution
		cell0 = walls[idx][0];
		cell1 = walls[idx][1];

		if (wSet.setFind(cell0) != wSet.setFind(cell1))		// if not same parent = not same set
		{
			wSet.setUnion(cell0, cell1);					// join set to remove walls
			walls[idx][0] = -1;								// walls are destroyed
			walls[idx][1] = -1;
		}

		idx ++;
	}
}


// print maze in textual format
void mazeGenerator::printMazeText() const
{
	int idx0 = 0;
	int idx1 = 0;
	int baseRow = 0;
	int baseCol = 0;
	int vert = (rows *2) - 1;
	int wCount = ((cols - 1) * rows) + (rows - 1) * cols;

	string line = "";
	string **content;

	content = new string*[vert];

	for (int i = 0; i < vert; i ++)
		content[i] = new string[cols];

	for (int i = 0; i < vert; i ++)
	{
		for (int j = 0; j < cols; j ++)
		{
			if (i % 2 == 0)					// |
			{
			 	if (j == cols - 1)
			 		content[i][j] = "  |";

			 	else 
			 		content[i][j] = "   ";
			}

			else							// +
				content[i][j] = "  +";
		}
	}


	for (int i = 0; i < wCount; i ++)
	{
		if (walls[i][0] != -1)
		{
			idx0 = walls[i][0];
			idx1 = walls[i][1];

			if ((idx1 - idx0) == 1)						// insert vertical walls
			{
				if (idx0 >= cols)						// not first row
				{
					baseRow = idx0/cols;				// num / cols to determine row
					baseCol = (baseRow * cols);			// to get base cell #, we multiply row * col
					baseRow = (baseRow * 2);			// we double the row count b/c (2 types of walls)
					baseCol = idx0 - baseCol;			// we subtract base cell # by cell # to get col
					content[baseRow][baseCol] = "  |";	// insert vertical wall
				}

				else									// first row
				{
					baseRow = 0;						// first row has index of 0 for vertical
					baseCol = idx0;						// column should match since cell # start from 0
					content[baseRow][baseCol] = "  |";	// insert vertical wall
				}
			}

			else if ((idx1 - idx0) == cols)				// insert horizontal walls
			{
				if (idx0 >= cols)						// not first row
				{
					baseRow = idx0/cols;				// num / cols to determine row
					baseCol = (baseRow * cols);			// to get base cell #, we multiply row * col
					baseRow = (baseRow * 2) + 1;		// we double the row count and add 1 b/c (2 types of walls)
					baseCol = idx0 - baseCol;			// we subtract base cell # by cell # to get col
					content[baseRow][baseCol] = "--+";	// insert horizontal wall
				}

				else									// first row
				{
					baseRow = 1;						// first row has index of 1 for horizontal
					baseCol = idx0;						// column should match since cell # start from 0
					content[baseRow][baseCol] = "--+";	// insert horizontal wall
				}

			}

		}
	}


	line = "+";
	for (int i = 0; i < cols; i ++)	
	{
		if (i == 0)
			line += "  +";

		else
			line += "--+";
	}

	cout << line << endl;


	for (int i = 0; i < vert; i ++)
	{
		if (i % 2 == 0)
			cout << "|";

		else 
			cout << "+";

		for (int j = 0; j < cols; j ++)
			cout << content[i][j];

		cout << endl;
	}

	line = "+";
	for (int i = 0; i < cols; i ++)
	{
		if (i == cols - 1)
			line += "  +";

		else
			line += "--+";
	}

	cout << line << endl;

	for (int i = 0; i < vert; i ++)
		delete[] content[i];

	delete[] content;
}


// re-order walls array in random order using permutations method
// select a random indesx, swap w/ last & repeat shrinking in size
void mazeGenerator::randomize()
{
	int wCount = ((cols - 1) * rows) + (rows - 1) * cols;
	int idx = 0;
	int temp = 0;

	for (int i = wCount - 1; i > 0; i --)
	{
		idx = rand() % i + 1;
		temp = walls[idx][0];
		walls[idx][0] = walls[i][0];
		walls[i][0] = temp;

		temp = walls[idx][1];
		walls[idx][1] = walls[i][1];
		walls[i][1] = temp;

	}

}