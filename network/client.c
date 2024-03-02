#include "csapp.h"
#include <stdlib.h>
#define MAX_SIZE 8192

int main(int argc, char **argv) {
  /* Validate Input */
  if (argc < 3) {
    perror("Usage: ./client host port [file]\n");
    exit(1);
  }
  int port, clientfd;
  char *hostname = argv[1];
  if ((port = strtol(argv[2], NULL, 10)) < 0) {
    perror("Port number out of bounds\n");
    exit(1);
  }
  /* Create a connection */
  if ((clientfd = Open_clientfd(hostname, port)) < 0) {
    perror("Failed to open client\n");
    exit(1);
  }
  /* Send request and read response */
  rio_t rio;
  Rio_readinitb(&rio, clientfd);
  char request[MAX_SIZE];
  snprintf(request, MAX_SIZE,
           "GET /index.html HTTP/1.1\r\n"
           "Host: %s\r\n"
           "\r\n",
           hostname);
  Rio_writen(clientfd, request, strlen(request));
  ssize_t nbytes;
  char response[MAX_SIZE];
  /* Read response */
  while ((nbytes = Rio_readlineb(&rio, response, MAX_SIZE)) != 0) {
    if (nbytes < 0) {
      perror("No bytes read\n");
      exit(1);
    }
    printf("%s", response);
  }
  Close(clientfd);
  return 0;
}
