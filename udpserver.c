#include <stdio.h>
#include <winsock2.h> // Include Winsock library for Windows

#pragma comment(lib, "Ws2_32.lib") // Link Winsock Library

void func(SOCKET sockfd, struct sockaddr_in *cliaddr, int len);

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in servaddr, cliaddr;
    int len;

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
        servaddr.sin_addr.s_addr = INADDR_ANY;

        // Binding socket
        if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
            printf("\nBind failed. Error Code : %d\n", WSAGetLastError());
            closesocket(sockfd);
            WSACleanup();
            return 1;
        } else {
            printf("\nBind successfully\n");
            len = sizeof(cliaddr);

            // Receive data from client
            func(sockfd, &cliaddr, len);
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void func(SOCKET sockfd, struct sockaddr_in *cliaddr, int len) {
    int num, sum_of_divisors = 0;
    char result[50];

    // Receive number from client
    recvfrom(sockfd, (char*)&num, sizeof(num), 0, (struct sockaddr*)cliaddr, &len);
    printf("\nReceived number: %d\n", num);

    // Calculate the sum of divisors of the number (excluding the number itself)
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum_of_divisors += i;
        }
    }

    // Check if the number is perfect
    if (sum_of_divisors == num) {
        sprintf(result, "%d is a perfect number", num);
    } else {
        sprintf(result, "%d is not a perfect number", num);
    }

    printf("\nResult: %s\n", result);

    // Send the result back to the client
    sendto(sockfd, result, sizeof(result), 0, (struct sockaddr*)cliaddr, len);
}