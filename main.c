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

u8 inputArr[16], outputArr[16];
u8 mrand[16];// = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
u8 keyArr[16] = {0x14, 0x5D, 0xD6, 0x1C, 0xE1, 0xF1, 0x9B, 0x84, 0x96, 0x3C, 0x09, 0x8C, 0x84, 0xDF, 0x1B, 0x98};
int i;

int main(int argc, char** argv) {    
    printf("KEY: ");
    for (i = 0; i < 16; i++) {
        printf("%02x", keyArr[i]);
    }

    genRand(mrand);
    f1(keyArr, mrand);
    f2_5(keyArr);
    genAutn();
    
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