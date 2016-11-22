#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <string.h>

char response[] = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>Bye-bye baby bye-bye</title>"
"<style>body { background-color: #111 }"
"h1 { font-size:4cm; text-align: center; color: black;"
" text-shadow: 0 0 2mm white}</style></head>"
"<body><h1>CPP port 8080 : No query received</h1></body></html>\r\n";

int main()
{
  char aString[4096];
  int one = 1, client_fd = 0;
  struct sockaddr_in svr_addr, cli_addr;
  socklen_t sin_len = sizeof(cli_addr);
  aString[0]='\0';
  strcpy(aString, "UNH+1+DENBUR:05:1:1A+510UH3UMNN DCD++KE58F22A+++DCR QTY+TO:5:SEC UNT+4+1'");

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    err(1, "can't open socket");

  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

  int port = 8080;
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = INADDR_ANY;
  svr_addr.sin_port = htons(port);

  if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
    close(sock);
    err(1, "Can't bind");
  }

  listen(sock, 5);
  while (1) {
    client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);
    printf("got connection\n");

    if (client_fd == -1) {
      perror("Can't accept");
      continue;
    }

    //write(client_fd, response, sizeof(response) - 1); /*-1:'\0'*/
    write(client_fd, aString, strlen(aString));
    /*int bytes_read = read(client_fd, aString, 4096);
    aString[bytes_read] = '\0';
    if(bytes_read > 0)
      write(client_fd, aString, strlen(aString));
    else
      write(client_fd, response, sizeof(response) - 1);
    */
    close(client_fd);
  }
}
