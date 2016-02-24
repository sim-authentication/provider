/* 
 * File:   main.c
 * Author: Marco Heumann
 *
 * Created on 29. Januar 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef u_int8_t u8;

u8 inputArr[16], keyArr[16], outputArr[16];
int i;

/*
 * 
 */
int main(int argc, char** argv) {
    char* keyStr = "2b7e151628aed2a6abf7158809cf4f3c";
    char* inputStr = "6bc1bee22e409f96e93d7e117393172a";
    char* temp;
    temp = malloc(3);
    for (i = 0; i < 16; i++) {
        strncpy(temp, &keyStr[i * 2], 2);
        keyArr[i] = strtol(temp, NULL, 16);

        strncpy(temp, &inputStr[i * 2], 2);
        inputArr[i] = strtol(temp, NULL, 16);
    }
    free(temp);

    encrypt(inputArr, keyArr, outputArr);
        
    // teste in1()
    in1();

    // teste temp()
    temp_m();
    
    return (EXIT_SUCCESS);
}

