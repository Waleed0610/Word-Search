#include <iostream>
#include <fstream>
#include<string>
using namespace std;

int* gridse(char** grid, int gridrows, int gridcolumns, char* word);  //this function takes all words  of the list turn by turn and searches them by the following function

int* seall(char** grid, int gridrows, int gridcolumns, int row, int columns, char* word);  //searches the word in all 8 directions

void cordinates(char** list, int noofwords, char** grid, int rows, int cols); //function to show start and end cordinates  of a word

int strlen(char* str);   //function to calculate strlen

char** wordslist(int tc, int readline);   //reads the list of search words from file 

char** readandsearchgrid(int rows, int cols, int readline);  //reads the grid from file

int* gridse(char** grid, int gridrows, int gridcolumns, char* word)  //this function searches all words
{
	int* returnarr = new int[4];
	int* arr = new int[3];

	for (int row = 0; row < gridrows; row++)
	{
		for (int columns = 0; columns < gridcolumns; columns++)
		{
			arr = seall(grid, gridrows, gridcolumns, row, columns, word);
			if (arr[0] == 1)
			{
				returnarr[0] = row;  //start cordinates of word
				returnarr[1] = columns;

				returnarr[2] = arr[1];  //end cordinates of the word
				returnarr[3] = arr[2];
				return returnarr;
			}

		}

	}
	delete[]arr;
	returnarr[0] = -1;
	returnarr[1] = 0;
	returnarr[2] = 0;
	returnarr[3] = 0;
	return returnarr;

}
int* seall(char** grid, int gridrows, int gridcolumns, int row, int columns, char* word)
{
	int columnderection[] = { -1, 1, 0, 0, 1, -1, 1, -1 };
	int rowderetion[] = { 0, 0, 1,-1, 1, 1, -1, -1 };     // 8 directions  in the order (right to left),(left to right),(top to bottom),(bottom to top),(top left to bottom right),(top right to bottom left),(bottom left to top right),(bottom right to top left)
	

	int* arr = new int[3];    //this array will keep have 1 at 0 position if word is found and record of the end cordinates of the word
							 //if word not found then the array wil will have -1 at 0 position

	if (grid[row][columns] != word[0])   //checks if the cordinate have the first letter of word 
	{
		arr[0] = -1;
		arr[1] = 0;
		arr[2] = 0;
		return  arr;
	}


	int length = strlen(word);


	for (int i = 0; i < 8; i++)  //for 8 directions
	{
		int j;
		int moveRow = row + rowderetion[i];
		int moveCol = columns + columnderection[i];

		// First character is already checked, match remaining 
		// characters 
		for (j = 1; j < length; j++)  //as first letter is found so starting form 1
		{
			// If out of bound break 
			if (moveRow >= gridrows || moveRow < 0 || moveCol >= gridcolumns || moveCol < 0)
			{
				break;
			}


			// If not matched,  break 
			if (grid[moveRow][moveCol] != word[j])
			{
				break;
			}



			moveRow = moveRow + rowderetion[i];   //moves in the specuific direction 
			moveCol = moveCol + columnderection[i];
		}


		if (j == length) //if the word is found then j will be equal to length
		{
			moveRow = moveRow - rowderetion[i];
			moveCol = moveCol - columnderection[i];

			arr[0] = 1;
			arr[1] = moveRow;   //end cordinates of the word
			arr[2] = moveCol;

			return arr;
		}

	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return  arr;
}

char** wordslist(int tc, int readline)
{
	ifstream file("Input.txt");
	if (file)
	{

		string dummyLine;
		for (int i = 0; i < readline; i++)      //this skips all the data before words 
		{
			getline(file, dummyLine);
		}

		char** wordList = new char* [tc];

		int i = 0;

		while (i < tc)
		{
			char abc[80];

			file.getline(abc, 80);

			int cols = 0;
			cols = strlen(abc);

			wordList[i] = new char[cols + 1];

			int j = 0;
			for (j = 0; j < cols; j++) //deep copying
			{
				wordList[i][j] = abc[j];
			}
			wordList[i][j] = '\0';
			i++;
		}

		return wordList;
	}

}
char** readandsearchgrid(int rows, int cols, int readline)
{
	ifstream file("Input.txt");
	if (file)
	{

		string dummyLine;
		for (int i = 0; i < readline; i++) //this skips all the data before grid
		{
			getline(file, dummyLine);
		}

		int i = 0;
		char** Grid = new char* [rows];
		while (i < rows)
		{
			char abc[80];

			file.getline(abc, 80);



			Grid[i] = new char[cols + 1];

			int j = 0;
			int k = 0;
			for (j = 0; j < cols && k < (cols + cols - 1); j++) //deep copying
			{

				Grid[i][j] = abc[k];
				k += 2;

			}
			Grid[i][j] = '\0';
			i++;
		}

		return Grid;
	}

}
int main()
{
	ifstream fin("Input.txt");
	if (fin)
	{
		int rows, cols, tc;

		fin >> rows >> cols >> tc;
		int readLine; 
		char** grid = 0;
		readLine = 2;
		grid = readandsearchgrid(rows, cols, readLine);     
		

		char** list = 0;
		readLine = 2 + rows;  //list of words start after grid 
		list = wordslist(tc, readLine);         //reads the list

		cordinates(list, tc, grid, rows, cols);
		cout<<"***************************************************************************************";
		cout<<endl;
		cout<<endl;   
		cout <<"                         Alhumdulilah Task is Done"<<endl;
	}
}
void cordinates(char** list, int noofwords, char** grid, int rows, int cols)  //function to show start and cordinates  of a word
{
	ofstream file("Output.txt");
	if (file)
	{
		for (int i = 0; i < noofwords; i++)
		{

			int* result = new int[4];

			result = gridse(grid, rows, cols, list[i]);  //this function returns the cordinates

			if (result[0] == -1)
			{
				file << "NOT FOUND";
			}
			else
			{
				file << "{" << result[0] << "," << result[1] << "}" << "{" << result[2] << "," << result[3] << "}";
			}
			file << endl;
			delete[]result;


		}
	}
	file.close();
}
int strlen(char* str)  
{
	int length = 0;
	int a = 0;

	while (str[a] != '\0')
	{
		length++;
		a++;
	}

	return length;
}
