#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
void print2D(int **arr);
int bSize;
int **compPath;
int **nums;
int **tempPath;
int lngth = 0;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

//Prints out the puzzle from the file
void printPuzzle(char** arr) { //Takes in 2d Array of characters
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    // Print out the puzzle grid
    //For loop for size of puzzle grid
    for (int i = 0; i < bSize; ++i) {
        //Another loop for printing
        for (int j = 0; j < bSize; ++j) { 
            //Gives the character at jth column of ith row.
            printf("%c ", *(*(arr + i) + j)); 
        }
        //New Line
        printf("\n"); 
    }
    printf("\n");
}

//Prints out result
void print2D(int **arr){ //Takes in 2d array of integers
    for (int i = 0; i < bSize; i++){
        for (int j = 0; j < bSize; j++){
            //Uses pointer arithmetic, \t to separate numbers, gives the integer at jth column of ith row
            printf("%d\t", *(*(arr + i) + j));
        }
        //Checks if current row is not last row. means more rows to print
        if (i != bSize - 1){ 
            printf("\n"); 
        }
    }
}

//Uses recursion & returns 1 for succeeding and 0 for failing
int searchPuzzleHelper(char **arr, char *word, int i, int j, int index, int **path){
    //Checks if character in puzzle grid at current position matches character in word at current index
    if (*(*(arr + i) + j) == *(word + index)){
        //If matched, current position is stored in path array at index, keeps track of path taken to find word
        *(*(path + index) + 0) = i;
        *(*(path + index) + 1) = j;
        //Checks if current index is at end of word
        if (index + 1 == lngth){
            //Nested for loop that copies the path stored in a 2d array to another 2d array for more processing
            for (int i = 0; i < lngth; i++){
                for (int j = 0; j < 2; j++){
                    *(*(compPath + i) + j) = *(*(path + i) + j);
                }
            }
            return 1;
        }
        //The following does checks that is called recursively for the next character of the word
        //Top middle
        if (i > 0){
            if (searchPuzzleHelper(arr, word, i - 1, j, index + 1, path)){
                return 1;
            }
        }
        //Middle right
        if (j < bSize - 1){
            if (searchPuzzleHelper(arr, word, i, j + 1, index + 1, path)){
                return 1;
            }
        }
        //Bottom right
        if ((i < bSize - 1) && (j < bSize - 1)){
            if (searchPuzzleHelper(arr, word, i + 1, j + 1, index + 1, path)){
                return 1;
            }
        }
        //Middle left
        if (j > 0){
            if (searchPuzzleHelper(arr, word, i, j - 1, index + 1, path)){
                return 1;
            }
        }
        //Bottom middle
        if (i < bSize - 1){
            if (searchPuzzleHelper(arr, word, i + 1, j, index + 1, path)){
                return 1;
            }
        }
        //Top left corner
        if ((i > 0) && (j > 0)){
            if (searchPuzzleHelper(arr, word, i - 1, j - 1, index + 1, path)){
                return 1;
            }
        }
        //Top right corner
        if ((i > 0) && (j < bSize - 1)){
            if (searchPuzzleHelper(arr, word, i - 1, j + 1, index + 1, path)){
                return 1;
            }
        }
        //Bottom left
        if ((i < bSize - 1) && (j > 0)){
            if (searchPuzzleHelper(arr, word, i + 1, j - 1, index + 1, path)){
                return 1;
            }
        }
        return 0;
    }
    else{
        return 0;
    }
}

// This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
void searchPuzzle(char** arr, char* word) {
    // Convert the search word to uppercase
    int index = 0;
    while (*(word + index) != 0){
        if ((*(word + index) >= 97) && (*(word + index) <= 122)){
            *(word + index) -= 32;
        }
        // Gets the length of the word
        lngth++;
        index++;
    }
    //Stores path of found word
    nums = (int **)malloc(bSize * sizeof(int *));
    //-1's if full hasn't been found. Contains the path if all letters have been found
    compPath = (int **)malloc(lngth * sizeof(int *));
    // Temp path. The function changes this as it calculates the path
    tempPath = (int **)malloc(lngth * sizeof(int *));
    int truex = 0;
    int truey = 0;
    int reset = 0;
    int count = 0;
    
    //Initializes output array and nums is initialized with 0s
    for (int i = 0; i < bSize; i++){
        *(nums + i) = (int *)malloc(bSize * sizeof(int));
        for (int j = 0; j < bSize; j++){
            (*(*(nums + i) + j)) = 0;
        }
    }
    //Initialize the two path arrays which is filled with -1s
    for (int i = 0; i < lngth; i++){
        *(compPath + i) = (int *)malloc(2 * sizeof(int));
        *(tempPath + i) = (int *)malloc(2 * sizeof(int));
        for (int j = 0; j < 2; j++){
            (*(*(compPath + i) + j)) = -1;
            (*(*(tempPath + i) + j)) = 0;
        }
    }

    // Calculates path for every index
    for (int i = 0; i < bSize; i++){
        for (int j = 0; j < bSize; j++){
            // Recursive Function
            searchPuzzleHelper(arr, word, i, j, 0, tempPath);
            // Checks if path was found
            for (int k = 0; k < lngth; k++){
                for (int l = 0; l < 2; l++){
                    //Checks if valid path position is recorded in compPath array
                    if (*(*(compPath + k) + l) != -1){
                        reset = 1;
                        break;
                    }
                }
                if (reset){
                    break;
                }
            }
            // Resets paths for next search
            if (reset){
                //Does reverse loop
                for (int k = lngth - 1; k > -1; k--){
                    //Gets the x&y coordinates from the k element of compPath
                    truex = *(*(compPath + k) + 0);
                    truey = *(*(compPath + k) + 1);
                    //Shifts digits one position to the left
                    *(*(nums + truex) + truey) *= 10;
                    //Makes sure path positions are numbered from 1 to lngth in nums array
                    *(*(nums + truex) + truey) += k + 1;
                }
                //Resets compPath and tempPath arrays to -1 and 0 for next seach operation
                for (int k = 0; k < lngth; k++){
                    for (int l = 0; l < 2; l++){
                        //Sets the lth element of compPath to -1 and tempPath to 0
                        *(*(compPath + k) + l) = -1;
                        *(*(tempPath + k) + l) = 0;
                    }
                }
                //Means that the current path is processed and reset
                reset = 0;
                //Used to keep track of words found in grid
                count++;
            }
        }
    }
    //If there is no word there
    if (count == 0){
        printf("Word not found!\n");
    }
    //If there is a word found
    else{
        printf("Word found!\n");
        printf("Printing the search path:\n");
        //Prints the array at the end
        print2D(nums);
        //Meant to ask for new command after finishing the code
        printf("\n");
    }
}  