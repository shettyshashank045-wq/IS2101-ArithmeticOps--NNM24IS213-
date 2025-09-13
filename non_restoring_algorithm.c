#include <stdio.h>
#include <stdlib.h>

// Function to display binary form
void showBinary(int value, int size) {
    unsigned int flag = 1u << (size - 1);
    for (int i = 0; i < size; i++) {
        printf("%d", (value & flag) ? 1 : 0);
        flag >>= 1;
    }
}

// Non-Restoring Division
void nonRestoringDiv(int dividend, int divisor, int width) {
    int R = 0;              // Remainder (Accumulator)
    int Q = dividend;       // Quotient register
    int D = divisor;        // Divisor
    int steps = width;      // Number of iterations

    for (int k = 0; k < steps; k++) {
        // Shift left R and Q
        R = (R << 1) | ((Q >> (width - 1)) & 1);
        Q = (Q << 1) & ((1 << width) - 1);

        printf("Step %d:\n", k + 1);
        printf("After shift: R = "); showBinary(R, width + 1);
        printf(", Q = "); showBinary(Q, width); printf("\n");

        // Non-restoring decision
        if (R >= 0) {
            R = R - D;
            if (R >= 0) Q |= 1;   // Successful subtract → set Q LSB = 1
        } else {
            R = R + D;
            // Q LSB remains 0
        }

        printf("After operation: R = "); showBinary(R, width + 1);
        printf(", Q = "); showBinary(Q, width); printf("\n\n");
    }

    // Final correction
    if (R < 0) {
        R = R + D;
    }

    printf("Final Quotient Q = "); showBinary(Q, width);
    printf(" (%d)\n", Q);
    printf("Final Remainder R = "); showBinary(R, width + 1);
    printf(" (%d)\n", R);
}

int main() {
    int num, den, bits;
    printf("Enter Dividend: ");
    scanf("%d", &num);
    printf("Enter Divisor: ");
    scanf("%d", &den);
    printf("Enter number of bits: ");
    scanf("%d", &bits);

    nonRestoringDiv(num, den, bits);
    return 0;
}
