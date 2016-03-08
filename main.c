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

u8 inputArr[16], keyArr[16], outputArr[16];
u8 mrand[16] = {0x23, 0x55, 0x3c, 0xbe, 0x96, 0x37, 0xa8, 0x9d, 0x21, 0x8a, 0xe6, 0x4d, 0xae, 0x47, 0xbf, 0x35};
int i;

int main(int argc, char** argv) {
    char* stat_key = "465b5ce8b199b49faa5f0a2ee238a6bc";
    char* temp;
    temp = malloc(3);
    for (i = 0; i < 16; i++) {
        strncpy(temp, &stat_key[i * 2], 2);
        keyArr[i] = strtol(temp, NULL, 16);
    }
    free(temp);

    //genRand(mrand);
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
}