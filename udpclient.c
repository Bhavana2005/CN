#include <stdio.h>
#include <winsock2.h> // Include Winsock library for Windows

#pragma comment(lib, "Ws2_32.lib") // Link Winsock Library

void func(SOCKET sockfd, struct sockaddr_in *servaddr);

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in servaddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }

    // Creating socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    } else {
        printf("\nSocket is created\n");

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(43451);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        // Communicate with server
        func(sockfd, &servaddr);
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void func(SOCKET sockfd, struct sockaddr_in *servaddr) {
    int num;
    char result[50];  // Buffer to store the result from server
    int len = sizeof(*servaddr);

    // Get number from user
    printf("\nEnter a number to check if it is a perfect number: ");
    scanf("%d", &num);

    // Send the number to the server
    sendto(sockfd, (char*)&num, sizeof(num), 0, (struct sockaddr*)servaddr, len);

    // Receive the result from server
    recvfrom(sockfd, result, sizeof(result), 0, (struct sockaddr*)servaddr, &len);

    // Print the result received from the server
    printf("\n%s\n", result);
}