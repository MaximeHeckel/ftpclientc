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
#define PORT 21  /* Le port où le client se connectera */
#define ACK                   2
#define NACK                  3
#define REQUESTFILE           100
#define COMMANDNOTSUPPORTED   150
#define COMMANDSUPPORTED      160
#define BADFILENAME           200
#define FILENAMEOK            400
#define STARTTRANSFER         500
#define MAXDATASIZE 200 /* Tampon d'entrée */

int main(int argc, char *argv[])
{
	  int sockfd, numbytes;  
	  char buf[MAXDATASIZE];
    char username[10];
    char password[10];
    int bytes_received_command;
    char recv_data_command[1024];
    char command[6];
    struct hostent *he;
	  struct sockaddr_in their_addr; /* Adresse de celui qui se connecte */

	  if (argc != 2) {
		    fprintf(stderr,"usage: client hostname\n");
		    exit(1);
	  }

	  if ((he=gethostbyname(argv[1])) == NULL) {  /* Info de l'hôte */
		    herror("gethostbyname");
		    exit(1);
	  }

	  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		    perror("socket");
		    exit(1);
	  }

	  their_addr.sin_family = AF_INET;      /* host byte order */
	  their_addr.sin_port = htons(PORT);    /* short, network byte order */
	  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	  bzero(&(their_addr.sin_zero), 8);     /* zero pour le reste de struct */

	  printf("* client connect() vers serveur ...\n");
	  if (connect(sockfd, (struct sockaddr *)&their_addr, \
					  sizeof(struct sockaddr)) == -1) {
		    perror("connect");
		    exit(1);
	  } 
	  printf("* client recv() ...\n");
    
	  while(1)
		{
		  if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
			    perror("recv");
			    exit(1);
		  }

		  buf[numbytes] = '\0';
      printf("%s\n",buf);

		  send(sockfd, "USER",4,0);
      printf("Please enter username\n");
      gets(username);
      if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
			    perror("recv");
			    exit(1);
		  }
      printf("%s\n", buf);

      send(sockfd, "PASS",4,0);
      printf("Please enter password\n");
      gets(password);

      if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
			    perror("recv");
			    exit(1);
		  }
      printf("%s\n", buf);


      
      
           
      gets(command);
      printf("%s\n",command);

      send(sockfd, command, strlen(command),0);
      bytes_received_command=recv(sockfd,recv_data_command,1024,0);
      recv_data_command[bytes_received_command] = '\n';
      printf ("%s \n", recv_data_command);
	    }
    
	  return 0;
}
