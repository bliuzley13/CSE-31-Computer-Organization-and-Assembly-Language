#include <stdio.h>

int main() {
    int x = 0, y = 0, *px, *py;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    //Points px to x and py to y
    px = &x;
    py = &y;

    //Prints out values and addresses of px and py 
    printf("px address: %p\n", (void*)px);
    printf("px value: %p\n", px);
    printf("py address: %p\n", (void*)py);
    printf("py value: %p\n", py);

    //Prints out addresses of x and y
    printf("x = %d\n", x);
    printf("y = %d\n", y);

    //Outputs contents of arr
    //Initialize pointer with 0th address
    int *ptr = arr;
    for (int i = 0; i < 10; i++){
        printf("arr[%d] = %d\n", i, *ptr);
        ptr++;
    }

    //Array as same as pointer
    printf("arr address: %p\n", (void*)arr);
    printf("arr[0] address: %p\n", (void*)&arr[0]);

    return 0;
}