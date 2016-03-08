#include <stdio.h>
#include <stdlib.h>
#include "rijndael.h"

typedef unsigned char u8;

void in1();
void f1(u8*, u8*);
void convertToBin(u8*, u8*);
void convertToHex(u8*, u8*);
void genRand(u8*);

u8 opc[16] = {0xcd, 0x63, 0xcb, 0x71, 0x95, 0x4a, 0x9f, 0x4e, 0x48, 0xa5, 0x99, 0x4e, 0x37, 0xa0, 0x2b, 0xaf};
u8 c1[16] = {0x7C, 0x1E, 0xE3, 0x6E, 0x98, 0xC2, 0x74, 0x40, 0xCA, 0x1D, 0x58, 0xF7, 0xE8, 0xD3, 0x7D, 0x2F};
u8 c2[16] = {0xC1, 0xFC, 0xBC, 0xAB, 0xC7, 0x3E, 0xE4, 0xA2, 0xF3, 0x62, 0x82, 0x11, 0xB8, 0x7A, 0xED, 0x04};
u8 c3[16] = {0x16, 0x07, 0x87, 0xD0, 0x24, 0xC2, 0xA5, 0x1D, 0xC4, 0x21, 0x4A, 0x3A, 0xE4, 0x3F, 0x5A, 0x34};
u8 c4[16] = {0x69, 0xA6, 0xF7, 0x01, 0x54, 0x77, 0x69, 0x17, 0x85, 0xD8, 0x0C, 0xA1, 0xBB, 0x7A, 0x0D, 0x93};
u8 c5[16] = {0xFD, 0x2E, 0xF6, 0x92, 0xE4, 0x14, 0xFB, 0x2E, 0x93, 0xE3, 0x9C, 0x0A, 0x92, 0xD0, 0xE9, 0xAB};
u8 binArr[128], temp[16],res[8], ak[6];

int i;

void f1(u8* keyArr, u8* mrand) {
    // a 128-bit value constructed from SQN and AMF and used in the computation of the functions f1
    // and f1*.
    // 
    // A 128-bit value IN1 is constructed as follows:
    // IN1[0] .. IN1[47] = SQN[0] .. SQN[47]
    // IN1[48] .. IN1[63] = AMF[0] .. AMF[15]
    // IN1[64] .. IN1[111] = SQN[0] .. SQN[47]
    // IN1[112] .. IN1[127] = AMF[0] .. AMF[15]
    //
    // TEMP is a 128-bit value used within the computation of the functions.
    // TEMP = E[RAND XOR OP C ] K (while K is keysting)
    // OUT1 = E[TEMP XOR rot(IN1 XOR OPc , r1) XOR c1]k XOR OPc
    // r1=1F, r2= 3A, r3=01, r4=3F, r5=08

    // dummy values for SQN and AMF
    u8 sqn[6] = {0xff, 0x9b, 0xb4, 0xd0, 0xb6, 0x07};
    u8 amf[2] = {0xb9, 0xb9};
    u8 in1[16];
    u8 toEncrypt[16];
    u8 out1[16];

    printf("\nDUMMY_SQN: ");
    for (i = 0; i < 6; i++) {
        printf("%hhx", sqn[i]);
    }
    
    printf("\nDUMMY_AMF: ");
    for (i = 0; i < 2; i++) {
        printf("%hhx", amf[i]);
    }

    // create IN1
    for (i = 0; i < 6; i++) {
        in1[i] = sqn[i];
        in1[i + 8] = sqn[i];
    }
    for (i = 0; i < 2; i++) {
        in1[i + 6] = amf[i];
        in1[i + 14] = amf[i];
    }

    // print IN1
    printf("\nIN1: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", in1[i]);
    }

    // print dummy RAND
    printf("\nRAND: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", mrand[i]);
    }
    printf("\nOPc: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", opc[i]);
    }

    for (i = 0; i < 16; i++) {
        toEncrypt[i] = mrand[i] ^ opc[i];
    }
    encrypt(toEncrypt, keyArr, temp);
    
    printf("\r\nTEMP: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", temp[i]);
    }

    // generate most inner value for calculation of out1
    // TEMP XOR rot(IN1 XOR OPc , r1) XOR c1
    // r1=1F, r2= 3A, r3=01, r4=3F, r5=08
    for (i = 0; i < 16; i++) {
        out1[i] = in1[i]^opc[i];
    }

    convertToBin(out1, binArr);
    rotWord(binArr, 128, 0x40);
    convertToHex(binArr, out1);

    for (i = 0; i < 16; i++) {
        out1[i] = temp[i]^out1[i]^0x00;//c1[i];
    }
    
    // encrypt generated values
    encrypt(out1, keyArr, out1);
    printf("\nOutput of 2nd encryption: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", out1[i]);
    }

    // XOR with OPc
    for (i = 0; i < 16; i++) {
        out1[i] ^= opc[i];
    }

    // test output for out1
    printf("\nOUT1: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", out1[i]);
    }
}

void f2_5(u8* keyArr) {
    u8* out2;
    out2 = malloc(16);

    for (i = 0; i < 16; i++) {
        out2[i] = temp[i] ^ opc[i];
    }
    convertToBin(out2, binArr);
    rotWord(binArr, 128, 0x3a); // replace with correct r1-value later
    convertToHex(binArr, out2);

    for (i = 0; i < 16; i++) {
        out2[i] ^= c2[i];
    }
    encrypt(out2, keyArr, out2);

    for (i = 0; i < 16; i++) {
        out2[i] ^= opc[i];
    }

    printf("\r\nAK: ");
    for (i = 0; i < 6; i++) {
        ak[i] = out2[i];
        printf("%hhx", ak[i]);
    }
    printf("\r\nRES: ");
    for (i = 7; i < 16; i++) {
        res[i - 7] = out2[i];
        printf("%hhx", res[i - 7]);
    }
}

void convertToBin(u8* hexArr, u8* binArr) {
    int i, j;
    unsigned char mask = 1;

    for (j = 0; j < 16; j++) {
        for (i = 0; i < 8; i++) {
            binArr[j * 8 + i] = (hexArr[j] & (mask << (7 - i))) != 0;
        }
    }
}

void convertToHex(u8* binArr, u8* hexArr) {
    int i, j, k = 0, temp, arrpos; // k iterates through binArr, i is for calculating each 8 bit to hex, j equals base for calculating hex values in each octet

    for (arrpos = 0; arrpos < 16; arrpos++) {
        temp = 0;
        j = 128;
        for (i = 0; i < 8; i++) {
            temp = temp + (binArr[k] * j);
            j = j / 2;
            k++;
        }
        j = 1;
        hexArr[arrpos] = temp;
    }
}

void genRand(u8* mrand) {
    int i;
    time_t t;
    srand((unsigned) time(&t));
    for(i = 0;i<16;i++) {
        mrand[i]=rand()%16;
    }
}