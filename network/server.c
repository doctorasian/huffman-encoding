/**
        @file
        @author Francis Nguyen <fn87@drexel.edu>
        @date 02 March 2024
        @section DESCRIPTION

        This program acts as a basic server which constantly
        accepts connections and reads requests in the form
        "GET /path HTTP/1.1\r\n\r\n".
        The server responds by sending file contents to the
        client if the path is valid.
 */
#include "csapp.h"
#include <string.h>

/**
Logs established connections to the server
@param clientaddr contains information about client
*/
void logClientInfo(struct sockaddr_in clientaddr) {
  struct hostent *hp;
  char *haddrp;
  hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                     sizeof(clientaddr.sin_addr.s_addr), AF_INET);
  haddrp = inet_ntoa(clientaddr.sin_addr);
  printf("Server connected to %s (%s)\n", hp->h_name, haddrp);
}

/**
Wrapper function for send(); sends response to client
@param connfd is the client's file descriptor
@param response is the message to send to client
*/
void sendResponse(int connfd, char *response) {
  send(connfd, response, strlen(response), 0);
}

/**
Handles HTTP GET requests sent to the server
Parses path to file and sends file contents to client (connfd)
@param connfd is the client's file descriptor
@param request is a pointer to the request buffer
@param nbytes is reused to store num bytes read
*/
void processRequest(int connfd, char *request, size_t nbytes) {
  char get[5], path[MAXLINE], http[10], *response;
  if (sscanf(request, "%s %s", get, path) == 2) {
    printf("%s path: %s, %s\n", get, path, http);
    if (strcmp(get, "GET") != 0) {
      sendResponse(connfd, "HTTP/1.1 405 METHOD NOT ALLOWED\n");
      return;
    }
  } else {
    sendResponse(connfd, "Usage: GET /path HTTP/1.1\\r\\n\\r\\n\n");
    return;
  }
  if (sscanf(request, "%s %s %s", NULL, NULL, http) == 1) {
    if (strcmp(http, "HTTP/1.1\\r\\n\\r\\n") != 0) {
      sendResponse(connfd, "HTTP/1.1 400 BAD SYNTAX\n");
      return;
    }
  }
  int filefd;
  if ((filefd = open(path, O_RDONLY)) < 0) {
    sendResponse(connfd, "HTTP/1.1 404 FILE NOT FOUND\n");
    return;
  }
  sendResponse(connfd, "HTTP/1.1 200 OK\n");
  char filebuf[MAXLINE];
  size_t sentBytes;
  rio_t tempRio;
  Rio_readinitb(&tempRio, filefd);
  while ((nbytes = Rio_readnb(&tempRio, filebuf, MAXLINE)) > 0) {
    if ((sentBytes = send(connfd, filebuf, nbytes, 0)) == -1) {
      perror("Failed to send file to client.\n");
      break;
    }
  }
  close(filefd);
}

int main(int argc, char **argv) {
  /* Validate arguments */
  if (argc < 2) {
    printf("Usage: ./server port\n");
    exit(EXIT_FAILURE);
  }
  int port, listenfd, connfd;
  struct sockaddr_in clientaddr;
  socklen_t clientlen = sizeof(clientaddr);
  port = strtol(argv[1], NULL, 10);

  /* Set up listening socket */
  listenfd = Open_listenfd(port);
  rio_t rio;
  char buf[MAXLINE];
  size_t nbytes;

  while (1) {
    /* Block until we receive a request */
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    logClientInfo(clientaddr);
    Rio_readinitb(&rio, connfd);
    while ((nbytes = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
      processRequest(connfd, buf, nbytes);
    }
    close(connfd);
    printf("Connection with client closed.\n");
  }
  close(listenfd);
  return 0;
}
