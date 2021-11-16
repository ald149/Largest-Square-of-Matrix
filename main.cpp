/*
Name: Andrew Darby
PSU ID; ald149
Course: CMPSC 465
Due: 10/31/2021
Time of last Modification: 10/28/2021
What does it do: Program reads in integers from txt file.  The integers make up a matrix of 1's and 0's.  The program inputs the 
size of the matrix and the values, and then uses dynamic programming to determine the area of the largest square of 1's
*/

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

void squareArea(vector<vector<int>>, int, int);
int min(int, int, int);

int main()
{
	ifstream inFile;		            //create input stream object
	string readFile = "input.txt";		// name of input txt file
	vector<int> wholeFile;				// vector to store entire contents of txt file
	int num = 0;						// int to store values read in from text file
	int row = 0;						// int stores value of number of rows in matrix 
	int col = 0;						// int stores value of number of columns in matrix
	int n = 0;							// int stores placeholder for front of vector
	vector<vector<int>> matrix;			// 2D vector to store values in matrix read in from txt file


	inFile.open(readFile);	            // open proj3 input file for X and O matrix
	if (inFile)				            // test success of file open
		cout << "file opened." << endl << endl;

	while (inFile >> num)				// while there are values in the .txt file read them as input
	{
		wholeFile.push_back(num);		// store input in vector wholeFile
	}

	wholeFile.pop_back();


	// while the wholeFile vector still contains values, process those values get matrix size and layout, then calculate
	// the max area of largest square of 1's
	while (!wholeFile.empty())			
	{
		
		row = wholeFile.front();				//size of row is first element
		wholeFile.erase(wholeFile.begin());		
		col = wholeFile.front();				//sizwe of columns is second element
		wholeFile.erase(wholeFile.begin());	
				
		// establish dimensions of 2D vector that stores matrix
		matrix.resize(row);
		for (int x = 0; x < row; x++)
		{
			matrix[x].resize(col);
		}

		// for loops store values of read in matrix in 2D vector and erases values as they are stored
		for (int i = 0; i < row; i++) {

			for (int j = 0; j < col; j++) {

				matrix[i][j] = wholeFile.at(n);
				wholeFile.erase(wholeFile.begin());
			}
		}
		
		squareArea(matrix, row, col);		// call to method that computes area of largest square of 1's

	}// end while loop

	inFile.close(); // close input txt file

}// end method main


// method uses Dynamic Programming to compute area of largest square of 1's in matrix of 1's and 0's
void squareArea(vector<vector<int>> matrix, int row, int col) {

	vector<vector<int>> area;	//2D vector to hold new matrix with secondary values

	// initilize 2D vector
	area.resize(row);
	for (int i = 0; i < row; i++)
	{
		area[i].resize(col);
	}

	// fill in first row same as in original matrix
	for (int i = 0; i < row; i++)
		area[i][0] = matrix[i][0];

	// fill in first column same as in original matrix
	for (int j = 0; j < col; j++)
		area[0][j] = matrix[0][j];

	//fill in rest of area matrix with updated values
	for (int i = 1; i < row; i++)
	{
		for (int j = 1; j < col; j++)
		{
			if (matrix[i][j] == 1)
				area[i][j] = min(area[i][j - 1], area[i - 1][j], area[i - 1][j - 1]) + 1; // call min method 
			else
				area[i][j] = 0;
		}
	}


	int maxElement = area[0][0];  // stores value of maximum element in new matrix area
	// computes max element in matrix
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (maxElement < area[i][j])
			{
				maxElement = area[i][j];
			}
		}
	}

	cout << "The area of the largest square of 1's is: " <<maxElement * maxElement << endl;
}

// method to determine min value of three matirx elements
int min(int x, int y, int z)
{
	int min = 0;
	if (x < y)
		min = x;
	else min = y;

	if (min < z)
		return min;
	else
		return z;

}// end method min

