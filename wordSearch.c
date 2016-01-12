/*
Name: Tyler Gauntlett
Course: COP 3502
Assignment: Word Search solver

COULD NOT GET RECURSION AND STRING CONCATENATION TO WORK, INCOMPLETE.
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MIN_STRING_LENGTH 3
#define MAX_STRING_LENGTH 19
const int DX_SIZE = 8;
const int DX[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int DY[] = { -1, 0, 1, -1, 1, -1, 0, 1 };


char** fillBoard(int rows, int cols);
char** createBoardArray(int rows, int cols);
void freeArray(char** board, int rows);
char **readFile(FILE *file, int wordCount);
void printArray(char** dictionaryArray, int wordCount);
int initializeProgram();
int binaryCharSearch(char*** sortedDictionary, char stringKey[MAX_STRING_LENGTH], int length);
int isInBounds(int x, int y, int i, int j);
char* searchBoard(int x, int y, int location, char*** board, char*** sortedDictionary, int length, int rows, int cols, int i);


int main() {
	
	if (initializeProgram() == 1){
		printf("File failed to open.");
	}

	system("pause");

	return 0;
}

int initializeProgram(){

	char **dictionaryArray = NULL;
	char **wordSearchBoard = NULL;
	char c[MAX_STRING_LENGTH];
	int wordCount, boardsToSolve, n = 1;

	// Opens dictionary file
	FILE *fileDictionary = fopen("dictionary.txt", "r");


	// Verifies that the file opened properly. 
	if (fileDictionary != NULL){

		// Reads in the number of words in the 
		// txt file based on the int on the first
		// line.
		fscanf(fileDictionary, "%i", &wordCount);

		// Calls a function that reads the file into a 2D
		// array.
		dictionaryArray = readFile(fileDictionary, wordCount);
	}

	else {
		return 1;
	}

	scanf("%i", &boardsToSolve);

	// Loops based on the number of
	// puzzles to be solved.
	while (boardsToSolve > 0){

		int rows, cols, i, j;

		scanf("%i", &rows);

		scanf("%i", &cols);

		wordSearchBoard = createBoardArray(rows, cols);

		printf("Words Found Grind #%i\n", n);

		for (i = 0; i < rows; i++){
			for (j = 0; j < cols; j++){
				
				// Copies the function finding words to a useable vairbale.
				strcpy(c, searchBoard(i, j, 0, &wordSearchBoard, &dictionaryArray, wordCount, rows, cols, 0));

				// Prints the word found from the board.
				printf("%s\n", c);

			}
		}

		n++;
		boardsToSolve--;
	}

	fclose(fileDictionary);

	// Frees the 2D array holding dicitonary.
	freeArray(dictionaryArray, wordCount);

	return 0;
}

// Allicates enough memory for the board
// for [rows][cols] int paramaters, and fills 
// the board with chars.
char** fillBoard(int rows, int cols) {

	char** board = malloc(sizeof(char*)*rows);

	int i;

	for (i = 0; i<rows; i++) {
		board[i] = malloc(sizeof(char)*cols);
		scanf("%s", board[i]);
	}

	return board;
}


// Takes in the user input for number of boards
// and board dimensions
char** createBoardArray(int rows, int cols){

		char** output = fillBoard(rows, cols);

		/*
		for (i = 0; i < rows; i++){
			printf("%s\n", output[i]);
		}
		*/

		return output;
}


// Dynamically allocates and fills a 2D array with
// words from a txt file.
char **readFile(FILE *file, int wordCount){

	char** dictionaryArray = NULL;
	char word[MAX_STRING_LENGTH];
	int i, wordLength;

		/* Here we allocate space a pointer for each word in the list.
		Note that the space for the words themselves is NOT allocated here. */
		dictionaryArray = (char **)malloc(wordCount * sizeof(char *));

		for (i = 0; i < wordCount; i++){

			// Reads in each word  
			fscanf(file, "%s", word);

			// Allocate one extra spot for the null character.
			wordLength = strlen(word) + 1;

			// Allocate space for this individual word.
			dictionaryArray[i] = (char *)malloc(wordLength);

			// Copy the word to the memory block.
			strcpy(dictionaryArray[i], word);

		}

		return dictionaryArray;

}


// Frees the dynamically allocated arrays
void freeArray(char** board, int rows) {
	int i;

	for (i = 0; i < rows; i++){
		free(board[i]);
	}

	free(board);
}

// Print function.
void printArray(char** dictionaryArray, int wordCount){
	int i;

	for (i = 0; i < wordCount; i++){
		printf("%s\n", dictionaryArray[i]);
	}
}

// Check if the location is inside the board bounderies.
int isInBounds(int x, int y, int i, int j){

	if (x >= 0 && y >= 0 && x < i && y < j){
		return 1;
	}

	return 0;
}


// Binary searches through the dictionary array looking
// for a match.
int binaryCharSearch(char*** sortedDictionary, char stringKey[MAX_STRING_LENGTH], int length){
	
	int start = 0;
	int end = length;

	while (start < end){
		int middle = (start + end) / 2;
		int compare = strcmp((*sortedDictionary)[middle], stringKey);
		if (compare < 0) {
			start = middle + 1;
		}
		else if (compare > 0) {
			end = middle;
		}
		else return 1;
	}

	return 0;
}


// create recursive compare function that utilizes DX[] 
// and DY[] to state true or false vaules. True continues 
// search, false ends the search at that index.
char* searchBoard(int x, int y, int location, char*** board, char*** sortedDictionary, int length, int rows, int cols, int i){

	char tempString[MAX_STRING_LENGTH];

	for (i = i; i < DX_SIZE; i++){

		// Checks if the location is inside the board.
		if (isInBounds(x, y, rows, cols) == 1){

			// Concatenate chars from the board on to tempString.
			// Run tempString
			//strcat(tempString, board[][]);

			// Returns the word from the word search if found
			// found in the dictionary.
			if (binaryCharSearch(sortedDictionary, tempString, length) == 1){
				return tempString;
			}
		}
	}

	// Recursively call the funciton until all possible moves have been checked.
	//return searchBoard(x, y, location, board, sortedDictionary, length, rows + DX[i], cols + DY[i], i);

	return "";
	
}
