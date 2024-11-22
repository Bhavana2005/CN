#include <stdio.h>
#include <string.h>

void bitStuffing(char *input) {
    int len = strlen(input);
    int count = 0;
    char output[2 * len]; // Output array that might be larger than input

    int j = 0; // Output index
    for (int i = 0; i < len; i++) {
        output[j++] = input[i];
        
        if (input[i] == '1') {
            count++;
            if (count == 5) {
                output[j++] = '0'; // Insert a '0' after 5 consecutive '1's
                count = 0;
            }
        } else {
            count = 0;
        }
    }

    output[j] = '\0'; // Null-terminate the output string
    printf("After Bit Stuffing: %s\n", output);
}

int main() {
    char input[100]; // Array to store user input
    printf("Enter a binary string (only '1' and '0'): ");
    scanf("%s", input); // User input for the binary string

    printf("Original Data: %s\n", input);
    bitStuffing(input);
    return 0;
}