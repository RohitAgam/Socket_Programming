//Server Side Code
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#define PORT 4000
char *strrev(char *str){
   char *p1, *p2;
   if (! str || ! *str)
      return str;
   for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2){
      *p1 ^= *p2;
      *p2 ^= *p1;
      *p1 ^= *p2;
   }
   return str;
}
main() {
   int server_fd, new_socket, valread;
   struct sockaddr_in address;
   char str[100];
   int addrlen = sizeof(address);
   char buffer[1024] = { 0 };
   int i, j, temp, k;
   int l;
   char* message = "Welcome to the server"; //initial message
   // Creating socket file descriptor
   if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      perror("Socket connection failed");
      exit(EXIT_FAILURE);
   }
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);
   if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) { //attack with socket 4000
      perror("Unable to bind with the socket 4000");
      exit(EXIT_FAILURE);
   }
   if (listen(server_fd, 3) < 0) {
      perror("Listning.....");
      exit(EXIT_FAILURE);
   }
   if ((new_socket = accept(server_fd, (struct sockaddr*)&address,(socklen_t*)&addrlen)) < 0) {
      perror("Accept");
      exit(EXIT_FAILURE);
   }
   // read string send by client
   valread = read(new_socket, str, sizeof(str));
   l = strlen(str);
   printf("\nString sent by client : %s\n", str);
   
   for(k = 0; str[k] != '\0'; k++) {
       if(str[k] >= 'a' && str[k] <= 'z') {
	   str[k] = str[k] - 32;
	}
   }
   strrev(str); //reverse the string
   send(new_socket, str, sizeof(str), 0);
   printf("\nReversed String is sent : \n");
}