#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
#define PORT 45678
#define BUF_SIZE 1024

int main(){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in recv_addr;
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (SOCKADDR*)&recv_addr, sizeof recv_addr);

    char buf[BUF_SIZE];

    struct  sockaddr_in sender_addr;
    int sender_addr_size = sizeof(sender_addr);

    while (TRUE)
    {
        int len = recvfrom(sock, buf, BUF_SIZE, 0,
        (SOCKADDR*)&sender_addr, &sender_addr_size);

        buf[len] = '\0';

        if(strcmp(buf, "die") == 0){
            printf("Goodbye");
            break;
        }

        printf("%s\n", buf);
    }
    

    closesocket(sock);

    WSACleanup();

    return 0;
}
