
#include <stdio.h>
//Chain Macro means you combine different macros into a single definition
// Macro definition
#define INSTAGRAM X
#define X 256

int main(){
    printf("Geeks for Geeks have %dK"
           " followers on Instagram",
           INSTAGRAM);
 
    return 0;
}
