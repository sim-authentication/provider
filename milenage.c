#include <stdio.h>
#include <stdlib.h>
#include "rijndael.h"

typedef unsigned char u8;

void f1star();
void in1();
void genTemp(u8*);

u8 opc[16] = {0x25, 0x50, 0x07, 0x6C, 0x5E, 0xF5, 0x9F, 0x77, 0xEE, 0xBE, 0xF1, 0xCA, 0x39, 0x91, 0x6E, 0xC8};
u8 output[16];
u8 c2[16] = {0x7C, 0x1E, 0xE3, 0x6E, 0x98, 0xC2, 0x74, 0x40, 0xCA, 0x1D, 0x58, 0xF7, 0xE8, 0xD3, 0x7D, 0x2F};

u8 res[8], ak[6];
int i;

void f1star() {
}

void in1() {
    // a 128-bit value constructed from SQN and AMF and used in the computation of the functions f1
    // and f1*.
    // 
    // A 128-bit value IN1 is constructed as follows:
    // IN1[0] .. IN1[47] = SQN[0] .. SQN[47]
    // IN1[48] .. IN1[63] = AMF[0] .. AMF[15]
    // IN1[64] .. IN1[111] = SQN[0] .. SQN[47]
    // IN1[112] .. IN1[127] = AMF[0] .. AMF[15]

    // dummy values for SQN and AMF
    int i;
    u8 in1[16];
    u8 sqn[6];
    u8 amf[2];

    printf("\n");
    printf("DUMMY_SQN: ");

    for (i = 0; i < 6; i++) {
        sqn[i] = i;
        printf("%hhx", sqn[i]);
    }

    printf("\n");
    printf("DUMMY_AMF: ");
    for (i = 6; i < 8; i++) {
        amf[i] = i;
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
    printf("\n");
    printf("IN1: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", in1[i]);
    }
}

void genTemp(u8* keyArr) {
    // TEMP is a 128-bit value used within the computation of the functions.
    // TEMP = E[RAND XOR OP C ] K (while K is keysting)
    int i;
    u8 dummy_rand[16];
    u8 dummy_k[16];
    u8 toEncrypt[16];

    // generate dummy RAND
    for (i = 0; i < 16; i++) {
        dummy_rand[i] = i;
    }

    // print dummy RAND
    printf("\n");
    printf("DUMMY_RAND: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", dummy_rand[i]);
    }
    printf("\n");
    printf("OPc: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", opc[i]);
    }

    for (i = 0; i < 16; i++) {
        toEncrypt[i] = dummy_rand[i] ^ opc[i];
        encrypt(toEncrypt, keyArr, output);
    }

    printf("\r\nTEMP: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", output[i]);
    }
}

void f2_5(u8* keyArr) {
    u8* out2;
    out2 = malloc(16);
    
    for (i = 0; i < 16; i++) {
        out2[i] = output[i] ^ opc[i];
    }
    rotWord(out2, 16, 0x3a);
    
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
        res[i-7] = out2[i];
        printf("%hhx", res[i-7]);
    }
}