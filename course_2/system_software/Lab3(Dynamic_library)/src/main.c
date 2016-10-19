#include <stdio.h>
#include "LibraryIOFunctions.h"
#include "LibraryMathFunctions.h"

int main() {
    printf("Using shared library functions!\n");

    printErrorMessage();
    printOkMessage();
    printf("sin(60) is %f\n", customSin(60));
    printf("cos(60) is %f\n", customCos(60));

    return 0;
}