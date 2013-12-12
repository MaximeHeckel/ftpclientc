#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <pthread.h>

#define SERVER_PORT 21
#define SERVER_ADDR "130.79.92.68"
#define MAXDATASIZE 100 /* Tampon d'entrée */

int main()
{

    int sock, bytes_received1,bytes_received2,bytes_received3;
    char *username,*password, recv_data1[1024],recv_data2[1024],recv_data3[1024];
    struct sockaddr_in server_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if (connect(sock, (struct sockaddr *)&server_addr, 
        sizeof(struct sockaddr)) == -1) {
        perror("Connect");
        exit(1);

    bytes_received1=recv(sock,recv_data1,1024,0);
    recv_data1[bytes_received1] = '\0';
    printf ("%s \n", recv_data1);
    gets(username);
    send(sock, username, strlen(username),0);

    bytes_received2=recv(sock,recv_data2,1024,0);
    recv_data2[bytes_received2] = '\0';
    printf ("%s \n", recv_data2);
    gets(password);
    send(sock, password, strlen(password),0);

    bytes_received3=recv(sock,recv_data3,1024,0);
    recv_data3[bytes_received3] = '\0';
    printf ("%s \n", recv_data3);

    close(sock);

    return 0;
}
