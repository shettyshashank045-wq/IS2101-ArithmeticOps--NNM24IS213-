#include <stdio.h>
#include <stdlib.h>

// Function to print binary of fixed width
void displayBinary(int number, int size) {
    for (int i = size - 1; i >= 0; i--) {
        printf("%d", (number >> i) & 1);
    }
}

// Restoring Division Algorithm
void restoringDivisionAlgo(int num, int den, int width) {
    int rem = 0;              // remainder register
    int quo = abs(num);       // quotient register (positive dividend)
    int div = abs(den);       // divisor (positive)
    int cycles = width;

    printf("Initial Values:\n");
    printf("rem = "); displayBinary(rem, width);
    printf("  quo = "); displayBinary(quo, width);
    printf("  div = "); displayBinary(div, width);
    printf("\n\n");

    while (cycles > 0) {
        // Shift left (rem, quo)
        int both = (rem << width) | quo;
        both <<= 1;
        rem = (both >> width) & ((1 << width) - 1);
        quo = both & ((1 << width) - 1);

        // Subtract divisor from remainder
        rem = rem - div;
        if (rem < 0) {
            rem = rem + div;   // restore remainder
            quo = quo & (~1);  // set LSB = 0
        } else {
            quo = quo | 1;     // set LSB = 1
        }

        cycles--;
    }

    // Adjust sign for final result
    int finalQuo = quo;
    int finalRem = rem;
    if ((num < 0) ^ (den < 0)) {
        finalQuo = -finalQuo;
    }
    if (num < 0) {
        finalRem = -finalRem;
    }

    printf("Final Quotient (Decimal): %d\n", finalQuo);
    printf("Final Quotient (Binary) : ");
    displayBinary(finalQuo & ((1 << width) - 1), width);
    printf("\n");

    printf("Final Remainder (Decimal): %d\n", finalRem);
    printf("Final Remainder (Binary) : ");
    displayBinary(finalRem & ((1 << width) - 1), width);
    printf("\n");
}

int main() {
    int dividend, divisor;
    printf("Enter Dividend: ");
    scanf("%d", &dividend);
    printf("Enter Divisor: ");
    scanf("%d", &divisor);

    if (divisor == 0) {
        printf("Error: Division by zero not allowed.\n");
        return 1;
    }

    restoringDivisionAlgo(dividend, divisor, 8); // using 8-bit division
    return 0;
}
