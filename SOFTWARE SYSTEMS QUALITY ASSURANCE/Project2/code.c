#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Function to convert hexadecimal to decimal
double hexToDecimal(const char hex[]) {
    double decimal = 0;
    int length = 0;

    // Calculate the length of the hex string
    while (hex[length] != '\0') {
        length++;
    }

    // Process each hex digit and convert to decimal
    for (int i = 0; i < length; i++) {
        char digit = hex[i];

        if (islower(digit)) {
            // Lowercase characters are not allowed
            printf("Error: Lowercase hexadecimal characters are not allowed.\n");
            exit(EXIT_FAILURE);
        }

        digit = toupper(digit);

        if (isdigit(digit)) {
            decimal += (digit - '0') * pow(16, length - i - 1);
        } else if (isxdigit(digit)) {
            decimal += (digit - 'A' + 10) * pow(16, length - i - 1);
        } else {
            // Invalid hex digit
            printf("Error: Invalid hexadecimal digit '%c'\n", hex[i]);
            exit(EXIT_FAILURE);
        }
    }

    return decimal;
}

int main() {
    char hex[31];

    while (1) {
        // Prompt user for input
        printf("Enter a hexadecimal number (up to 30 digits, uppercase): ");
        if (scanf("%30s", hex) != 1) {
            // Empty input or invalid input format
            printf("Error: Invalid input format\n");
            fflush(stdin); // Clear input buffer
            continue;
        }

        // Check if the input contains any lowercase characters
        int containsLowercase = 0;
        for (int i = 0; hex[i] != '\0'; i++) {
            if (islower(hex[i])) {
                containsLowercase = 1;
                break;
            }
        }

        if (containsLowercase) {
            printf("Error: Lowercase hexadecimal characters are not allowed.\n");
            continue;
        }

        // Convert hex to decimal
        double decimal = hexToDecimal(hex);

        // Check if the result is within the limits of a double
        if (isfinite(decimal)) {
            // Display the result
            printf("Hexadecimal: %s\n", hex);
            printf("Decimal: %.15f\n", decimal);
            break;
        } else {
            // Result exceeds the limits of a double
            printf("Error: Result exceeds the limits of a double\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
