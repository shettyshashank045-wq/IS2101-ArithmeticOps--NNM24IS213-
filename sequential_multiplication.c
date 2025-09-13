#include <stdio.h>
#include <stdlib.h>

// Absolute value function
int myAbs(int val) {
    return (val < 0) ? -val : val;
}

// Shift-Add Multiplication Algorithm
void shiftAddMul(int x, int y, int size) {
    int regA = 0;               // Accumulator
    int regQ = myAbs(y);        // Multiplier
    int regM = myAbs(x);        // Multiplicand
    int rounds = size;

    while (rounds > 0) {
        // Check if Q0 (LSB of regQ) = 1
        if (regQ & 1) {
            regA = regA + regM;
            printf("Step %d: Q0=1 -> regA = regA + regM = %d\n",
                   size - rounds + 1, regA);
        } else {
            printf("Step %d: Q0=0 -> No addition, regA = %d\n",
                   size - rounds + 1, regA);
        }

        // Right shift (regA, regQ)
        regQ = ((regA & 1) << (size - 1)) | (regQ >> 1);
        regA = regA >> 1;

        printf("After shifting: regA = %d, regQ = %d\n", regA, regQ);
        rounds--;
    }

    // Combine regA and regQ
    int product = (regA << size) | regQ;

    // Handle negative results
    if ((x < 0) ^ (y < 0)) {
        product = -product;
    }

    printf("\nFinal Product: %d\n", product);
}

int main() {
    int multiplicand, multiplier;
    printf("Enter Multiplicand: ");
    scanf("%d", &multiplicand);
    printf("Enter Multiplier: ");
    scanf("%d", &multiplier);

    shiftAddMul(multiplicand, multiplier, 8);  // 8-bit multiplication
    return 0;
}
