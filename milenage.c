#include <stdio.h>
#include <stdlib.h>
#include "rijndael.h"

typedef u_int8_t u8;

void f1star();
void in1();
void f1(u8*);

u8 opc[16] = {0x25, 0x50, 0x07, 0x6C, 0x5E, 0xF5, 0x9F, 0x77, 0xEE, 0xBE, 0xF1, 0xCA, 0x39, 0x91, 0x6E, 0xC8};
u8 c1[16] = { 0x7C, 0x1E, 0xE3, 0x6E, 0x98, 0xC2, 0x74, 0x40, 0xCA, 0x1D, 0x58, 0xF7, 0xE8, 0xD3, 0x7D, 0x2F};
u8 c2[16] = { 0xC1, 0xFC, 0xBC, 0xAB, 0xC7, 0x3E, 0xE4, 0xA2, 0xF3, 0x62, 0x82, 0x11, 0xB8, 0x7A, 0xED, 0x04};
u8 c3[16] = { 0x16, 0x07, 0x87, 0xD0, 0x24, 0xC2, 0xA5, 0x1D, 0xC4, 0x21, 0x4A, 0x3A, 0xE4, 0x3F, 0x5A, 0x34};
u8 c4[16] = { 0x69, 0xA6, 0xF7, 0x01, 0x54, 0x77, 0x69, 0x17, 0x85, 0xD8, 0x0C, 0xA1, 0xBB, 0x7A, 0x0D, 0x93};
u8 c5[16] = { 0xFD, 0x2E, 0xF6, 0x92, 0xE4, 0x14, 0xFB, 0x2E, 0x93, 0xE3, 0x9C, 0x0A, 0x92, 0xD0, 0xE9, 0xAB};

void f1star() {
}

void f1(u8* keyArr) {
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
    u8 sqn[6];
    u8 amf[2];
    u8 in1[16];
    u8 dummy_rand[16];
    u8 dummy_k[16];
    u8 toEncrypt[16];
    u8 output[16];

    printf("\nDUMMY_SQN: ");

    for (i = 0; i < 6; i++) {
        sqn[i] = i;
        printf("%x", sqn[i]);
    }

    printf("\nDUMMY_AMF: ");
    for (i = 6; i < 8; i++) {
        amf[i] = i;
        printf("%x", amf[i]);
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
        printf("%x", in1[i]);
    }

    // generate dummy RAND
    for (i = 0; i < 16; i++) {
        dummy_rand[i] = i;
    }

    // print dummy RAND
    printf("\nDUMMY_RAND: ");
    for (i = 0; i < 16; i++) {
        printf("%x", dummy_rand[i]);
    }
    printf("\nOPc: ");
    for (i = 0; i < 16; i++) {
        printf("%x", opc[i]);
    }

    for (i = 0; i < 16; i++) {
        toEncrypt[i] = dummy_rand[i] ^ opc[i];
        encrypt(toEncrypt, keyArr, output);
    }

    printf("\r\nTEMP: ");
    for (i = 0; i < 16; i++) {
        printf("%2x", output[i]);
    }
}

void genTemp(u8* keyArr) {
    // TEMP is a 128-bit value used within the computation of the functions.
    // TEMP = E[RAND XOR OP C ] K (while K is keysting)
    int i;




}