#include <stdio.h>
#include <string.h>

void byteStuffing(char *input, int len) {
    char output[2 * len]; // Output array that might be larger than input
    int j = 0; // Output index
    char ESC = 0x7D; // Escape character
    char FLAG = 0x7E; // Flag character
    
    for (int i = 0; i < len; i++) {
        if (input[i] == FLAG) {
            output[j++] = ESC; // Insert escape character
            output[j++] = FLAG; // Stuffed flag byte
        } else if (input[i] == ESC) {
            output[j++] = ESC; // Insert escape character
            output[j++] = ESC; // Stuffed escape byte
        } else {
            output[j++] = input[i]; // Otherwise, just copy the byte
        }
    }

    // Print stuffed data
    printf("After Byte Stuffing: ");
    for (int i = 0; i < j; i++) {
        printf("%02X ", (unsigned char)output[i]); // Print hex values of stuffed bytes
    }
    printf("\n");
}

int main() {
    char input[100]; // Array to store user input
    printf("Enter the data (in hexadecimal, no spaces): ");
    
    // Read the input data as a string of hex characters (without spaces)
    char ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && i < 100) {
        input[i++] = ch;
    }

    printf("Original Data: ");
    for (int j = 0; j < i; j++) {
        printf("%02X ", (unsigned char)input[j]);
    }
    printf("\n");

    byteStuffing(input, i); // Perform byte stuffing
    return 0;
}