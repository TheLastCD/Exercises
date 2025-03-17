// https://www.geeksforgeeks.org/macros-and-its-types-in-c-cpp/
#include <stdio.h>

//Object type Macro
//replaces the Macro name with a defined value/expression
// mostly only useful for constants or simple values

// Macro definition
#define DATE 31

int main(){
  
    // Print the message
    printf("Lockdown will be extended"
           " upto %d-MAY-2020",
           DATE);
    return 0;
}


