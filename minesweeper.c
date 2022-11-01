#define _CRT_SECURE_NO_WARNINGS   
#include <stdio.h>  
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define SIZE 22


/* The program simulates the game "Minesweeper" */
/* Writing by Michal, 25.12.20 */


void printMenu();
void buildingboard(int row, int cole, char table[][SIZE], char minestable[][SIZE]);
void printBoard(int row, int cole, char table[][SIZE], char minestable[][SIZE]);
void buildingF(int row, int cole, char table[][SIZE]);
int buildingMines(int row, int cole, char minestable[][SIZE], char table[][SIZE]);
void checkMove(int row, int cole, char table[][SIZE], char minestable[][SIZE], int rowselection, int coleselection);
int findNearSpace(int row, int cole, int rowselection, int coleselection, char table[][SIZE], char minestable[][SIZE]);
void gameManagment(int row, int cole, char table[][SIZE], char minestable[][SIZE], int rowselection, int coleselection);
int findNearMines(int row, int cole, char table[][SIZE], char minestable[SIZE][SIZE]);
void userCheat(char table[][SIZE], char minestable[][SIZE], int y);
int youWin(int row, int cole, char table[][SIZE], char minestable[][SIZE]);


void main()
{
	int userchoise = 0;
	int i = 0, j = 0;
	int rowselection = 0, coleselection = 0;
	int row = 0, cole = 0;
	char table[SIZE][SIZE];
	char minestable[SIZE][SIZE];
	minestable[i][j] = '*';


	printMenu();
	scanf("%d", &userchoise);
	switch (userchoise)
	{
	case 1:
		//user choise = 1
		row = 8, cole = 8;
		buildingboard(row, cole, table, minestable);
		printBoard(row, cole, table, minestable);
		buildingMines(row, cole, minestable, table);

		break;
	case 2:
		//user choise = 2
		row = 12, cole = 12;
		buildingboard(row, cole, table, minestable);
		printBoard(row, cole, table, minestable);
		buildingMines(row, cole, minestable, table);
		break;
	case 3:
		//user choise = 3
		row = 15, cole = 15;
		buildingboard(row, cole, table, minestable);
		printBoard(row, cole, table, minestable);
		buildingMines(row, cole, minestable, table);
		break;
	case 4:
		//user choise = 4
		printf("please choose your row and colum\n");
		scanf("%d %d", &row, &cole);
		break;
	case 0:
		//user choise = 0, user choose exit
		printf("goodbye\n");
		break;
	default:
		printf("Invalid choise\n");
		break;
	}
	if (userchoise == 4)
	{
		buildingboard(row, cole, table, minestable);
		printBoard(row, cole, table, minestable);
		buildingMines(row, cole, minestable, table);
	}
	if (userchoise > 0 && userchoise <= 4)
		gameManagment(row, cole, table, minestable, rowselection, coleselection);

}

/* function to print the initial menu */
void printMenu()
{

	printf("Welcome to Minesweeper!");
	printf("\n\nPlease choose one of the following options and enter it's number:");

	printf("\n\n1 - for size 8X8");
	printf("\n\n2 - for size 12X12");
	printf("\n\n3 - for size 15X15");
	printf("\n\n4 - for custom size");
	printf("\n\n0 - Exit");


	printf("\n\n");
}

/* function to build the board */
void buildingboard(int row, int cole, char table[][SIZE], char minestable[][SIZE])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < cole; j++)
		{
			table[i][j] = 'X';
		}
	}

}

/* function to print the original board */
void printBoard(int row, int cole, char table[][SIZE], char minestable[][SIZE])
{
	printf("        ");
	for (int i = 0; i < cole; i++)
	{
		printf("%d   ", i);
	}
	printf("\n");
	printf("    ");
	for (int i = 0; i < cole - 1; i++)
	{
		printf("_____");
	}
	printf("\n");
	for (int i = 0; i < row; i++)
	{
		printf("   ");
		printf("%2d|", i);
		for (int j = 0; j < cole; j++)
		{
			if (j < 10)
			{
				printf(" %c |", table[i][j]);

			}
			else
			{
				printf("%2c  |", table[i][j]);

			}
		}
		printf("\n");
	}
	printf("    ");
	for (int i = 0; i < cole - 1; i++)
	{
		printf("_____");
	}
	printf("\n");
}

/* function to build the F */
void buildingF(int row, int cole, char table[][SIZE])
{
	table[row][cole] = 'F';
}

/* function to check if the move is valid */
void checkMove(int row, int cole, char table[][SIZE], char minestable[][SIZE], int rowselection, int coleselection)
{
	int i, j;


	if (rowselection == -1 && coleselection >= 1)
	{
		userCheat(table, minestable, coleselection);
		printBoard(row, cole, table, minestable);

	}
	else if (rowselection < 0 || rowselection > row - 1 || coleselection < 0 || coleselection > cole - 1 || table[rowselection][coleselection] == ' ' != table[rowselection][coleselection] == 'X')
	{
		printf("Invalid move, please enter a valid choice!\n");
	}
	else if (table[rowselection][coleselection] != 'X')
	{
		printf("Invalid move, please enter a valid choice!\n");
	}
	else if (coleselection < 0)
	{
		printf("Invalid move, please enter a valid choice!\n");
	}
	else
	{
		table[rowselection][coleselection] = minestable[rowselection][coleselection];
		findNearSpace(row, cole, rowselection, coleselection, table, minestable);
	}
}

/* function to manage the game */
void gameManagment(int row, int cole, char table[][SIZE], char minestable[][SIZE], int rowselection, int coleselection)
{
	bool endGame = false;
	char letterChoise;

	while (!endGame)
	{
		printf("please enter your row, colum and your choise- F/O :\n");
		scanf("%d%d", &rowselection, &coleselection);
		char ch = getchar();
		int win;
		scanf("%c", &letterChoise);

		if (letterChoise == 'F')
		{
			buildingF(rowselection, coleselection, table);
		}
		else
		{
			if (rowselection < row || coleselection < cole &&  coleselection >= 1)
			{
				checkMove(row, cole, table, minestable, rowselection, coleselection);
				win = youWin(row, cole, table, minestable)
				if (win == 1)
				{
					endGame = true;
					table = minestable;
				}
				if (table[rowselection][coleselection] == '*')
				{
					printf("You've hit the bomb! Game over!\n");
					endGame = true;
					table = minestable;
				}
			}
			if (rowselection == -1)
			{
				userCheat(table, minestable, coleselection);
			}

		}
		printBoard(row, cole, table, minestable);
	}
}
/* function to build the mines  */
int buildingMines(int row, int cole, char minestable[][SIZE], char table[][SIZE])
{
	int j = 0, numOfMines = 0;
	int i = 0, randomrow, randomcole;
	srand(time(NULL));

	while (numOfMines < sqrt(row*cole))
	{

		randomrow = rand() % row;
		randomcole = rand() % cole;
		if (minestable[randomrow][randomcole] != '*')
		{
			minestable[randomrow][randomcole] = '*';
			numOfMines++;
		}

	}

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < cole; j++)
		{
			if (minestable[i][j] != '*')
			{
				numOfMines = findNearMines(i, j, minestable, minestable);
				if (numOfMines > 0)
				{
					minestable[i][j] = findNearMines(i, j, minestable, minestable) + 48;
				}
				else
				{
					minestable[i][j] = ' ';
				}

			}
		}
	}
}

/* function to find where are near mines */
int findNearMines(int row, int cole, char table[][SIZE], char minestable[SIZE][SIZE])
{
	int mines = 0;
	// Check up, down, left, right.
	if (table[row - 1][cole] == '*' && row - 1 >= 0)
		mines++;
	if (table[row + 1][cole] == '*' && row + 1 <= 22)
		mines++;
	if (table[row][cole - 1] == '*' && cole - 1 >= 0)
		mines++;
	if (table[row][cole + 1] == '*' && cole + 1 >= 22)
		mines++;
	// Check all diagonal directions
	if (table[row - 1][cole + 1] == '*' && row - 1 >= 0 && cole + 1 <= 22)
		mines++;
	if (table[row - 1][cole - 1] == '*' && row - 1 >= 0 && cole - 1 >= 0)
		mines++;
	if (table[row + 1][cole + 1] == '*' && row + 1 <= 22 && cole - 1 >= 0)
		mines++;
	if (table[row + 1][cole - 1] == '*' && row + 1 <= 22 && cole + 1 <= 22)
		mines++;
	return mines;
}

/* function to find where are near space */
int findNearSpace(int row, int cole, int rowselection, int coleselection, char table[][SIZE], char minestable[][SIZE])
{
	if (minestable[rowselection][coleselection] != ' ')
	{
		table[rowselection][coleselection] = minestable[rowselection][coleselection];
		return;
	}
	else
	{
		if (minestable[rowselection][coleselection] != '*')
		{
			table[rowselection][coleselection] = minestable[rowselection][coleselection];
			// Check up, down, left, right.
			if (rowselection < row - 1 && table[rowselection + 1][coleselection] == 'X')
			{
				findNearSpace(row, cole, rowselection + 1, coleselection, table, minestable);
			}
			if (coleselection < cole - 1 && table[rowselection][coleselection + 1] == 'X')
			{
				findNearSpace(row, cole, rowselection, coleselection + 1, table, minestable);
			}
			if (rowselection > 0 && table[rowselection - 1][coleselection] == 'X')
			{
				findNearSpace(row, cole, rowselection - 1, coleselection, table, minestable);
			}
			if (coleselection > 0 && table[rowselection][coleselection - 1] == 'X')
			{
				findNearSpace(row, cole, rowselection, coleselection - 1, table, minestable);
			}
			// Check all diagonal directions
			if (rowselection > 0 && coleselection < cole - 1 && table[rowselection - 1][coleselection + 1] == 'X')
			{
				findNearSpace(row, cole, rowselection - 1, coleselection + 1, table, minestable);
			}
			if (rowselection > 0 && coleselection > 0 && table[rowselection + 1][coleselection - 1] == 'X')
			{
				findNearSpace(row, cole, rowselection - 1, coleselection - 1, table, minestable);
			}
			if (rowselection < row - 1 && coleselection < cole - 1 && table[rowselection + 1][coleselection + 1] == 'X')
			{
				findNearSpace(row, cole, rowselection + 1, coleselection + 1, table, minestable);
			}
			if (rowselection < row - 1 && coleselection > 0 && table[rowselection + 1][coleselection - 1] == 'X')
			{
				findNearSpace(row, cole, rowselection + 1, coleselection - 1, table, minestable);
			}
		}
	}

}

/* function to help cheat*/
void userCheat(char table[][SIZE], char minestable[][SIZE], int y)
{
	int count = 0;
	int i = 0, j;
	printf("%d %d\n", count, y);
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE && count < y; j++)
		{
			if (table[i][j] == 'X' && minestable[i][j] != '*')
			{
				table[i][j] = minestable[i][j];
				count += 1;
			}
		}
	}

}

/* function to let the player know he won*/
int youWin(int row, int cole, char table[][SIZE], char minestable[][SIZE])
{
	int countX = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < cole; j++)
		{
			if (table[i][j] == 'X' && minestable[i][j] != '*')
			{
				countX = countX + 1;
			}
		}
	}
	if (countX == 0)
	{
		printf("you won!! congragolations! CHAMPION!");
	}
}



