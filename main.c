/* 
 * File:   main.c
 * Author: Marco Heumann
 *
 * Created on 29. Januar 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char u8;

void rotWord(u8*, int, int);
void convertToBin(u8*, u8*);

u8 inputArr[16], keyArr[16], outputArr[16], mrand[16];
int i;

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

    // teste f1()
    genRand(mrand);
    f1(keyArr, mrand);

    //test f2_5()
    f2_5(keyArr);

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
    reverse(array + size - amt, amt - 1);
    reverse(array, size - 1);
}