#include "solve_quadratic.h"

#include <stdio.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 4096

#define NO_ERROR 0
#define SOLUTION_ERROR 1
#define INPUT_ERROR 2

int main() {
    double a = 0,
           b = 0,
           c = 0,
           x1 = 0,
           x2 = 0;
    printf("Equation solver\n");
    printf("I solve ax^2 + bx + c = 0\n");
    printf("Enter a b c:\n");

    char input_str[INPUT_BUFFER_SIZE];
    memset(input_str, 0, INPUT_BUFFER_SIZE);
    char* check_str = NULL;
    while ((check_str = fgets(input_str, INPUT_BUFFER_SIZE, stdin))) {
        int stat = sscanf(input_str, "%lg %lg %lg", &a, &b, &c);
        if (stat == 3) {
            break;
        }
        printf("Sorry, I did't understand you. Please enter a b c as numbers or press Ctrl+D to exit:\n");
    }
    if (!check_str) {
        // Got EOF
        return NO_ERROR;
    }

    int numSolutions = solveQuadratic(a, b, c, &x1, &x2);
    switch (numSolutions) {
        case 0:
            printf("No solutions\n");
            break;
        case 1:
            printf("x = %g\n", x1);
            break;
        case 2:
            printf("x1 = %g, x2 = %g\n", x1, x2);
            break;
        case EQ_INFINITE_SOLUTIONS:
            printf("Infinite number of solutions\n");
            break;
        default:
            printf("Error while trying to solve equation\n");
            return SOLUTION_ERROR;
    }

    return NO_ERROR;
}
