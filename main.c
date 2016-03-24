/* 
 * File:   main.c
 * Author: Marco Heumann
 *
 * Created on 29. Januar 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

typedef unsigned char u8;

void rotWord(u8*, int, int);
void convertToBin(u8*, u8*);

u8 inputArr[16], outputArr[16], auts[14];
u8 mrand[16]; // = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
u8 keyArr[16] = {0x14, 0x5D, 0xD6, 0x1C, 0xE1, 0xF1, 0x9B, 0x84, 0x96, 0x3C, 0x09, 0x8C, 0x84, 0xDF, 0x1B, 0x98};
int i, status;
int socket_desc, client_sock, c, read_size, optval;
struct sockaddr_in server, client;
char client_message[50], imsi[15], response_message[96];

int main(int argc, char** argv) {
    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(12345);

    //Bind
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof (server)) < 0) {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc, 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof (struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) & c);
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    //Receive a message from client
    while ((read_size = recv(client_sock, client_message, 50, 0)) > 0) {
        char* temp;
        temp = malloc(2);

        strncpy(temp, &client_message[0], 1);
        status = strtol(temp, NULL, 10);

        strncpy(imsi, &client_message[1], 15);
        
        response_message[0] = 50;

        if (status == 1) {
            for (i = 8; i < 22; i++) {
                strncpy(temp, &client_message[i * 2], 2);
                auts[i-8] = strtol(temp, NULL, 16);
            }
            
            //TODO: check MAC-S == XMAC-S
            f5star(keyArr, auts);
            response_message[0] = 51;
        }
        free(temp);

        genRand(mrand, &response_message[16]);
        f1(keyArr, mrand);
        f2_5(keyArr, &response_message[72]);
        genAutn(&response_message[48]);
        
        for(i = 0; i < 15; i++) {
            response_message[i+1] = imsi[i];
        }

        //Send the message back to client
        write(client_sock, response_message, strlen(response_message));
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }

    printf("\n\n");
    return (EXIT_SUCCESS);
}

void reverse(u8* a, int sz) {
    int i, j;
    for (i = 0, j = sz; i < j; i++, j--) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

void rotWord(u8* array, int size, int amt) {
    reverse(array, amt - 1);
    reverse(array + amt, size - amt - 1);
    reverse(array, size - 1);
}