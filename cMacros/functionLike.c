#include <stdio.h>

// Function-like Macro definition
#define min(a, b) (((a) < (b)) ? (a) : (b))

int main(){

    // Given two number a and b
    int a = 18, b = 76;

    printf("Minimum: %d", min(a, b));

    return 0;
}

