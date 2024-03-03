CC	= gcc
CFLAGS = -Wall -Og -I $(CSAPP_INC) -I . 
LDLIBS = -lpthread

all: client server

client: client.c csapp.o
	$(CC) -o client client.c csapp.o $(LDFLAGS) $(LDLIBS)

server: server.c csapp.o
	$(CC) -o server server.c csapp.o $(LDFLAGS) $(LDLIBS)

csapp.o: csapp.c
	$(CC) -c csapp.c

