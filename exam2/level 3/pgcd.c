#include <stdio.h> // Required for printf
#include <stdlib.h> // Required for atoi

// Function to calculate the Greatest Common Divisor (GCD) using the Euclidean algorithm.
// This function takes two integers, 'a' and 'b', and returns their GCD.
int gcd(int a, int b) {
    // The Euclidean algorithm states that if b is 0, the GCD is a.
    // Otherwise, the GCD of (a, b) is the same as the GCD of (b, a % b).
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(int argc, char *argv[]) {
    // Check if the number of command-line arguments is exactly 2 (program name + two numbers).
    // If not, print a newline and exit as per the problem requirements.
    if (argc != 3) {
        printf("\n");
        return 0; // Exit successfully
    }

    // Convert the first and second command-line arguments from strings to integers.
    // atoi (ASCII to integer) converts a string to an integer.
    // argv[0] is the program name, argv[1] is the first argument, argv[2] is the second.
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    // As per the problem description, inputs are "strictly positive integers".
    // The Euclidean algorithm expects positive integers.
    // If for some reason atoi returns 0 for a non-numeric string, it might still proceed.
    // However, given the problem context, we assume valid strictly positive integer inputs.
    // If the input was "0" or negative, the problem statement implies such cases won't occur for valid runs.

    // Calculate the GCD of the two numbers.
    int result = gcd(num1, num2);

    // Display the calculated GCD followed by a newline.
    printf("%d\n", result);

    // Return 0 to indicate successful execution.
    return 0;
}
