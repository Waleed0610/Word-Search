#include <iostream>
#include <ctime>
#include<cstdlib>
#include<fstream>
using namespace std;

//the following functions are defined in the order they are used

int RowCounter();  //this function counts the number of words in input.txt file to know the number of rows
int DimensionOfGrid(char** list);    //this function finds the dimension of the wordSearch Grid 
int StringLenght(char* str);   //function to calculate stringlenght

char** ReadStudentsListFromFile();       //function to read the file containing list of words
char** RemoveSpacesInWords(char** list, int rows);     //this function remove the spces between a word like WORD SEARCH has a space

char** GridIntialization(int max);      //this function intializes the grid with special character

int RandomSelect(int start, int max);  //this function is to generate a random number for rows and cols

void PlaceWord(char**& Grid, char** list);     //this function performs the following functions

int* SearchAllDirections(char** grid, int R, int C, int row, int col, char* word); //first searches a possible direction in which a word can be placed
                                                                                      
													//then places the word in that direction 

void PlaceWordLeftToRight(char**& Grid, char** list, int length, int wordNumber, int row, int col);				//to place the word in left to right direction
void PlaceWordRightToLeft(char**& Grid, char** list, int length, int wordNumber, int row, int col);				//to place the word in right to left direction
void PlaceWordTopToBottom(char**& Grid, char** list, int length, int wordNumber, int row, int col);				//to place the word in top to bottom direction
void PlaceWordBottomToTop(char**& Grid, char** list, int length, int wordNumber, int row, int col);				//to place the word in bottom to top direction
void PlaceWordTopLeftToBottomRight(char**& Grid, char** list, int length, int wordNumber, int row, int col);    //to place the word in top left to bottom right direction
void PlaceWordTopRightToBottomLeft(char**& Grid, char** list, int length, int wordNumber, int row, int col);    //to place the word in top right to bottom left direction
void PlaceWordBottomLeftToTopRight(char**& Grid, char** list, int length, int wordNumber, int row, int col);    //to place the word in bottom left to top right direction
void PlaceWordBottomRightToTopLeft(char**& Grid, char** list, int length, int wordNumber, int row, int col);    //to place the word in bottom right to top left direction

void FinalFill(char**& grid, int max);      //this function fills the grid with random alphabets when the words are placed

void SaveGrid(char** list, int max);        //function to save grid in file

void Deallocation(char** array, int rows);     //this function deallocates array and saves memory space 



int main()
{

	cout << endl<<endl;

	char** list = 0;
    int rows = RowCounter();      //counts the number of words in file for list array rows
    list = ReadStudentsListFromFile();     //reads the file into a 2d array

	char** finalListOfWords = 0;    
	finalListOfWords = RemoveSpacesInWords(list, rows);    //this function removes space between the words in 2d array

	char** grid = 0;               //word search grid
	int max = DimensionOfGrid(list);     //decides the dimensions of grid accordingly
	grid = GridIntialization(max);       

	cout << "Please wait your file is getting ready\n";
	cout<<endl;
	cout<<endl;
	PlaceWord(grid, finalListOfWords);    //places all words in grid

	FinalFill(grid, max);      //fills the remaining space in grid with random alphabets
	SaveGrid(grid, max);        //saves grid in file
	cout << "Alhumdulilah Task is Done"<<endl;

	return 0;
}
void Deallocation(char** array, int rows)     //this function deallocates array and saves memory space
{
	if (array != 0)
	{
		for (int i = 0; i < rows; i++)
		{
			delete[]array[i];

		}
		delete[] array;
	}
}

int RowCounter()   //this function counts the number of words in input.txt file
{
	ifstream file("Input.txt");
	int lineNumber = 1; //As it will not count last line so initial value is 1
	char ch;
	while (file)
	{
		file.get(ch);

		if (ch == '\n')
		{
			lineNumber++;
		}

	}
	file.close();
	return lineNumber;
}

int StringLenght(char* str)   //function to calculate stringlenght of a word without counting spaces in between it like WORD SEARCH has one space in between
{
	int stringLen = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			stringLen++;
		}
		i++;
	}

	return stringLen;
}



int DimensionOfGrid(char** list)     //this function finds the dimension of the wordSearch Grid
{
	int max = 0;
	int rows = RowCounter();     //the number of words in list

	int cols;
	for (int i = 0; i < rows; i++)
	{
		cols = StringLenght(list[i]);
		if (cols > max)
		{
			max = cols;
		}
	}
	if (max < rows)    //if the number of words in the grid are more than the length of the largest word in the list then it takes the number of words as dimmensions
	{
		max = rows;
	}
	max = max + max;

	return max;
}
char** RemoveSpacesInWords(char** list, int rows)     //this function removes spaces between words
{

	string s[100];

	for (int i = 0; i < rows; i++)
	{
		s[i] = list[i];
	}

	char** finalArray = new char* [rows];

	for (int i = 0; i < rows; i++)
	{
		int length = s[i].length();
		finalArray[i] = new char[length + 1];

		int k = 0;
		int j = 0;

		for (j = 0; j < length && k < length + 1; j++)
		{
			if (s[i][k] != ' ')
			{
				finalArray[i][j] = s[i][k];
				k++;
			}
			else
			{
				k++;
				finalArray[i][j] = s[i][k];
				k++;
			}
		}
		finalArray[i][j] = '\0';
	}
	return finalArray;
}

char** ReadStudentsListFromFile()     //reads the file containg words in a 2d array
{

	ifstream file("Input.txt");
	const int rows = RowCounter();

	char** List = new char* [rows];

	if (file)
	{

		char abc[80];
		

		int i = 0;

		while (i < rows)
		{

			file.getline(abc, 80);
			int cols = 0;
			cols = StringLenght(abc);

			List[i] = new char[cols + 1];

			int j = 0;
			for (j = 0; j < cols; j++)     //deep copying
			{
				List[i][j] = abc[j];
			}
			List[i][j] = '\0';
			i++;

		}
	}
	file.close();


	return List;

}
char** GridIntialization(int max)           //to intialize word Search grid with special character
{
	char** grid = new char* [max];

	for (int i = 0; i < max; i++)
	{
		grid[i] = new char[max + 1];

	}

	for (int i = 0; i < max; i++)
	{
		int j = 0;
		for (j = 0; j < max; j++)
		{


			grid[i][j] = '*';


		}
		grid[i][j] = '\0';
	}

	return grid;

}
void FinalFill(char**& grid, int max)     //after placing words fills the reamaining spaces with  random alphabets
{
	for (int i = 0; i < max; i++)
	{

		for (int j = 0; j < max; j++)
		{


			if (grid[i][j] == '*')
			{

				int r = rand() % 26;
				grid[i][j] = 'A' + r;
				
			}


		}

	}
}
int RandomSelect(int start, int max)        //randomly selects a number in a range from strat to max
{
	int random;
	srand(time(0));
	random = start + rand() % max;
	return random;
}

int* SearchAllDirections(char** grid, int R, int C, int row, int col, char* word)
{
	int rowDirection[] = { -1, 1, -1, 0,  1, 1, 0, -1 };     //these are the 8 random directions 
	int colDirection[] = { -1, 0,  0, -1, -1, 1, 1, 1 };

	int* arr = new int[3];    //this array will keep have 1 at 0 position if word is found and record of the end cordinates of the word
	
	if (grid[row][col] != '*')
	{
		arr[0] = -1;
		arr[1] = 0;
		arr[2] = 0;
		return  arr;
	}



	int length = StringLenght(word);

	for (int i = 0; i < 8; i++)
	{
		
		int k;
		int moveRow = row + rowDirection[i];
		int moveCol = col + colDirection[i];

		
		for (k = 1; k <= length; k++)
		{
			// If row and column exceed the boundaries of grid then break
			if (moveRow > R - 1 || moveRow <= 0 || moveCol > C - 1 || moveCol <= 0)
			{
				break;
			}


			
			if (grid[moveRow][moveCol] != '*')
			{
				break;
			}


			
			moveRow = moveRow + rowDirection[i];
			moveCol = moveCol + colDirection[i];
		}

		
		if (k == length + 1)     //if word can be placed 
		{

			arr[0] = 1;
			arr[1] = rowDirection[i];         //the direction  in which the word can be placed
			arr[2] = colDirection[i];

			return arr;
		}

	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return  arr;
}
void PlaceWordLeftToRight(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j <= length; j++)             // left to right
	{
		Grid[row][col - j] = list[wordNumber][j];
	}
}
void PlaceWordRightToLeft(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j <= length; j++)         //right to left
	{
		Grid[row][col + j] = list[wordNumber][j];
	}
}
void PlaceWordTopToBottom(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j <= length; j++)       //top to bottom
	{
		Grid[row + j][col] = list[wordNumber][j];
	}
}
void PlaceWordBottomToTop(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j <= length; j++)   //bottom to top
	{
		Grid[row - j][col] = list[wordNumber][j];
	}
}
void PlaceWordTopLeftToBottomRight(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j <= length; j++) //top left to bottom right
	{
		Grid[row + j][col + j] = list[wordNumber][j];
	}
}
void PlaceWordTopRightToBottomLeft(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j <= length; j++)   //top right to bottom left
	{
		Grid[row + j][col - j] = list[wordNumber][j];
	}
}
void PlaceWordBottomLeftToTopRight(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j <= length; j++)   //bottom left to top right
	{
		Grid[row - j][col + j] = list[wordNumber][j];
	}
}
void PlaceWordBottomRightToTopLeft(char**& Grid, char** list, int length, int wordNumber, int row, int col)
{
	for (int j = 0; j <= length; j++)  //bottom right to top left
	{
		Grid[row - j][col - j] = list[wordNumber][j];
	}
}
void PlaceWord(char**& Grid, char** list)
{
	int Rows = RowCounter();
	int max = DimensionOfGrid(list);

	for (int wordNumber = Rows - 1; wordNumber >= 0; wordNumber--)
	{
		int row, col;
		int* arr = 0;
		int length = StringLenght(list[wordNumber]);
		length = length - 1;

		//col = Rows - length - 1;
		int start = 1;
		row = RandomSelect(start,max);
		col = RandomSelect(length, max-length-1);
		row = row - 1;
		col = col - 1;
		arr = SearchAllDirections(Grid, max, max, row, col, list[wordNumber]);
		while (arr[0] == -1)
		{
			delete[] arr;
			arr = 0;
			//int* arr = new int [3];
			start = 1;
			row = RandomSelect(start, max);
			col = RandomSelect(length, max-length-1);
			col = col - 1;
			row = row - 1;
			arr = SearchAllDirections(Grid, max, max, row, col, list[wordNumber]);

		}
		if (arr[0] == 1)
		{
			if (arr[1] == 0 && arr[2] == -1)   //right to left
			{
				PlaceWordRightToLeft(Grid, list, length, wordNumber, row, col);
			}
			if (arr[1] == 0 && arr[2] == 1)   //left to right
			{
				PlaceWordLeftToRight(Grid, list, length, wordNumber, row, col);

			}
			if (arr[1] == 1 && arr[2] == 0)  //top to bottom
			{
				PlaceWordTopToBottom(Grid, list, length, wordNumber, row, col);
			}
			if (arr[1] == -1 && arr[2] == 0)    //bottom to top
			{
				PlaceWordBottomToTop(Grid, list, length, wordNumber, row, col);

			}
			if (arr[1] == 1 && arr[2] == 1)   //top left to bottom right
			{
				PlaceWordTopLeftToBottomRight(Grid, list, length, wordNumber, row, col);
			}
			if (arr[1] == 1 && arr[2] == -1)       //top right to bottom left
			{
				PlaceWordTopRightToBottomLeft(Grid, list, length, wordNumber, row, col);

			}
			if (arr[1] == -1 && arr[2] == 1)      //bottom left to top right
			{
				PlaceWordBottomLeftToTopRight(Grid, list, length, wordNumber, row, col);
			}
			if (arr[1] == -1 && arr[2] == -1)       //bottom right to top left
			{
				PlaceWordBottomRightToTopLeft(Grid, list, length, wordNumber, row, col);

			}
			delete[] arr;
			arr = 0;
		}
	}


}
void SaveGrid(char** list, int max)
{
	ofstream file("Output.txt");
	if (file)
	{
		file << endl << endl;

		for (int i = 0; i < max; i++)
		{
			//int cols = StringLenght(list[i]);
			for (int j = 0; j < max; j++)
			{
				if (list[i][j] != ' ')
				{
					if ((list[i][j] > 97 || list[i][j] == 97) && (list[i][j] < 122 || list[i][j] == 122))         //if the words placed in grid are lower case convert to upper
					{

						list[i][j] -= 32;
					}

					file << list[i][j] << " ";
				}

			}
			file << endl;
		}
	}
	file.close();

}
