#include <stdio.h>

int main() {
    int m = 10;
    int n = 5;
    int result;

    result = sum(m, n);
    printf("%d\n", result);

    return 0;
}

int sum(int a, int b) {
    return a + b;
}