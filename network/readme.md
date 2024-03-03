Instructions for running the programs below:

Run "make", which will compile client and server for you

PART A
Run ./client host port file

For example: ./client www.google.com 80 /index.html

PART B
Run ./server port
WARNING: Ports should be greater than 1024 (to avoid colliding with reserved ports)

For example: ./server 1025
             > On a separate terminal run telnet localhost 1025
             > GET ./test.txt HTTP/1.1\r\n\r\n
             > PLEASE NOTE: format is strict and must be in the form
                "GET /path HTTP/1.1\r\n\r\n"
