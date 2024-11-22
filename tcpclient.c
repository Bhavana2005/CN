#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serv_addr;
    char inputString[1024]; // Buffer for user input
    char buffer[1024] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("\n Socket creation error \n");
        WSACleanup();
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9090); // Use port 9090

    // Convert IPv4 and IPv6 addresses from text to binary form
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        closesocket(sock);
        WSACleanup();
        return -1;
    }

    // Prompt the user for input
    printf("Enter a string to check if it is a palindrome: ");
    fgets(inputString, sizeof(inputString), stdin);
    inputString[strcspn(inputString, "\n")] = 0; // Remove the newline character

    // Send the string to the server
    send(sock, inputString, strlen(inputString), 0);
    printf("String sent to server: %s\n", inputString);

    // Receive the response from the server
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Response from server: %s\n", buffer);

    // Close the socket
    closesocket(sock);
    WSACleanup();
    return 0;
}
