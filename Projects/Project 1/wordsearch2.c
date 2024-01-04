#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char **arr);
void searchPuzzle(char **arr, char *word);
void print2D(int **arr);

int bSize;

int **truePath;
int **nums;
int **path;
int lngth = 0;
// Main function, DO NOT MODIFY
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int  i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL)
    {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);

    // Allocate space for the puzzle block and the word to be searched
    char **block = (char **)malloc(bSize * sizeof(char *));
    char *word   = (char *)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for (i = 0; i < bSize; i++)
    {
        *(block + i) = (char *)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j)
        {
            fscanf(fptr, "%c ", *(block + i) + j);
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    //conversion to upper case
    int index = 0;

    while (*(word + index) != 0)
    {
        // 97 -> a
        // 122 -> z
        // 65 -> A
        // 90 -> Z
        if ((*(word + index) >= 97) && (*(word + index) <= 122))
        {
            *(word + index) -= 32;
        }
        lngth++;
        index++;
    }
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    printf("\n");
    for (int i = 0; i < bSize; i++)
    {
        free(*(block + i));
        free(*(nums + i));
    }
    for (int i = 0; i < lngth; i++)
    {
        *(truePath + i) = NULL;
        *(path + i)     = NULL;
        free(*(truePath + i));
        free(*(path + i));
    }
    free(truePath);
    free(path);
    free(block);
    free(word);
    free(nums);

    return 0;
}


void printPuzzle(char **arr)
{
    // This function will print out the complete puzzle grid (arr).
    // It must produce the output in the SAME format as the samples
    // in the instructions.
    // Your implementation here...
    for (int i = 0; i < bSize; i++)
    {
        for (int j = 0; j < bSize; j++)
        {
            printf("%c ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}


void print2D(int **arr)
{
    for (int i = 0; i < bSize; i++)
    {
        for (int j = 0; j < bSize; j++)
        {
            printf("%d\t", *(*(arr + i) + j));
        }
        if (i != bSize - 1)
        {
            printf("\n");
        }
    }
}


int searchPuzzleHelper(char **arr, char *word, int i, int j, int index, int **path)
{
    if (*(*(arr + i) + j) == *(word + index))
    {
        *(*(path + index) + 0) = i;
        *(*(path + index) + 1) = j;
        if (index + 1 == lngth)
        {
            for (int i = 0; i < lngth; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    *(*(truePath + i) + j) = *(*(path + i) + j);
                }
            }
            return 1;
        }
        //Middle left
        if (j > 0)
        {
            if (searchPuzzleHelper(arr, word, i, j - 1, index + 1, path))
            {
                return 1;
            }
        }
        //Middle right
        if (j < bSize - 1)
        {
            if (searchPuzzleHelper(arr, word, i, j + 1, index + 1, path))
            {
                return 1;
            }
        }
        //Top middle
        if (i > 0)
        {
            if (searchPuzzleHelper(arr, word, i - 1, j, index + 1, path))
            {
                return 1;
            }
        }
        //Bottom middle
        if (i < bSize - 1)
        {
            if (searchPuzzleHelper(arr, word, i + 1, j, index + 1, path))
            {
                return 1;
            }
        }
        //Top left corner
        if ((i > 0) && (j > 0))
        {
            if (searchPuzzleHelper(arr, word, i - 1, j - 1, index + 1, path))
            {
                return 1;
            }
        }
        //Top right corner
        if ((i > 0) && (j < bSize - 1))
        {
            if (searchPuzzleHelper(arr, word, i - 1, j + 1, index + 1, path))
            {
                return 1;
            }
        }
        //Bottom left
        if ((i < bSize - 1) && (j > 0))
        {
            if (searchPuzzleHelper(arr, word, i + 1, j - 1, index + 1, path))
            {
                return 1;
            }
        }
        //Bottom right
        if ((i < bSize - 1) && (j < bSize - 1))
        {
            if (searchPuzzleHelper(arr, word, i + 1, j + 1, index + 1, path))
            {
                return 1;
            }
        }
        return 0;
    }
    else
    {
        return 0;
    }
}


void searchPuzzle(char **arr, char *word)
{
    // This function checks if arr contains the search word. If the
    // word appears in arr, it will print out a message and the path
    // as shown in the sample runs. If not found, it will print a
    // different message as shown in the sample runs.
    // Your implementation here...
    //Output array
    nums = (int **)malloc(bSize * sizeof(int *));
    //-1's if the full hasn't been found. Will contain the path if all letters have been found.
    truePath = (int **)malloc(lngth * sizeof(int *));
    // Temp path. The function changes this as it calculates the path
    path = (int **)malloc(lngth * sizeof(int *));
    int truex   = 0;
    int truey   = 0;
    int reset   = 0;
    int counter = 0;

    //Initialize the output array
    for (int i = 0; i < bSize; i++)
    {
        *(nums + i) = (int *)malloc(bSize * sizeof(int));
        for (int j = 0; j < bSize; j++)
        {
            (*(*(nums + i) + j)) = 0;
        }
    }
    //Initialize the two path arrays
    for (int i = 0; i < lngth; i++)
    {
        *(truePath + i) = (int *)malloc(2 * sizeof(int));
        *(path + i)     = (int *)malloc(2 * sizeof(int));
        for (int j = 0; j < 2; j++)
        {
            (*(*(truePath + i) + j)) = -1;
            (*(*(path + i) + j))     = 0;
        }
    }

    // For every index calculate the path.
    for (int i = 0; i < bSize; i++)
    {
        for (int j = 0; j < bSize; j++)
        {
            searchPuzzleHelper(arr, word, i, j, 0, path);
            // Check to see if the path was found.
            for (int k = 0; k < lngth; k++)
            {
                for (int l = 0; l < 2; l++)
                {
                    if (*(*(truePath + k) + l) != -1)
                    {
                        reset = 1;
                        break;
                    }
                }
                if (reset)
                {
                    break;
                }
            }
            // Reset the paths for the next search.
            if (reset)
            {
                for (int k = lngth - 1; k > -1; k--)
                {
                    truex = *(*(truePath + k) + 0);
                    truey = *(*(truePath + k) + 1);
                    *(*(nums + truex) + truey) *= 10;
                    *(*(nums + truex) + truey) += k + 1;
                }
                for (int k = 0; k < lngth; k++)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        *(*(truePath + k) + l) = -1;
                        *(*(path + k) + l)     = 0;
                    }
                }
                reset = 0;
                counter++;
            }
        }
    }
    if (counter == 0)
    {
        printf("Word not found!");
    }
    else
    {
        printf("Word found!\n");
        printf("Printing the search path:\n");
        print2D(nums);
    }
}