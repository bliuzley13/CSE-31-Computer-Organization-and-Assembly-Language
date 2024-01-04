#include <stdio.h>
#include <stdlib.h>

struct Node {
    int iValue;
    float fValue;
    struct Node *next;
};

int main() {

    struct Node *head = (struct Node*) malloc(sizeof(struct Node));
    head->iValue = 5;
    head->fValue = 3.14;
	
	// Insert code here
	printf("Value of head: %p\n", head);
    printf("Address of head: %p\n", &head);
    printf("Address of iValue: %p\n", &head->iValue);
    printf("Address of fValue: %p\n", &head->fValue);
    printf("Address of next pointed by head: %p\n", (void*)head->next);

    // Example when run:
    // Value of head: 0x55ec25f642a0
    // Address of head: 0x7ffc32ee6440
    // Address of iValue: 0x55ec25f642a0
    // Address of fValue: 0x55ec25f642a4
    // Address of next pointed by head: (nil)

	return 0;
}