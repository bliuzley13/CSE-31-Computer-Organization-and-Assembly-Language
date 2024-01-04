
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

 int main() {
	int num;
	int *ptr;
	int **handle;

	num = 14;
	ptr = (int *)malloc(2 * sizeof(int));
	*ptr = num;
	handle = (int **)malloc(1 * sizeof(int *));
	*handle = ptr;

	// Insert code here
	//Addresses
	printf("Address of num: %p\n", &num); 
	printf("Address of ptr: %p\n", &ptr);
	printf("Address of handle: %p\n", &handle);

	//Example when run
	// Address of num: 0x7ffd5398b9c4
	// Address of ptr: 0x7ffd5398b9c8
	// Address of handle: 0x7ffd5398b9d0

	return 0;
} 

