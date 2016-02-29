#include <stdio.h>
#include <stdlib.h>
#include "rijndael.h"

typedef unsigned char u8;

void f1star();
void in1();
void f1(u8*);
void convertToBin(u8*, u8*);
void convertToHex(u8*, u8*);

u8 opc[16] ={ 0x25, 0x50, 0x07, 0x6C, 0x5E, 0xF5, 0x9F, 0x77, 0xEE, 0xBE, 0xF1, 0xCA, 0x39, 0x91, 0x6E, 0xC8};
u8 c1[16] = { 0x7C, 0x1E, 0xE3, 0x6E, 0x98, 0xC2, 0x74, 0x40, 0xCA, 0x1D, 0x58, 0xF7, 0xE8, 0xD3, 0x7D, 0x2F};
u8 c2[16] = { 0xC1, 0xFC, 0xBC, 0xAB, 0xC7, 0x3E, 0xE4, 0xA2, 0xF3, 0x62, 0x82, 0x11, 0xB8, 0x7A, 0xED, 0x04};
u8 c3[16] = { 0x16, 0x07, 0x87, 0xD0, 0x24, 0xC2, 0xA5, 0x1D, 0xC4, 0x21, 0x4A, 0x3A, 0xE4, 0x3F, 0x5A, 0x34};
u8 c4[16] = { 0x69, 0xA6, 0xF7, 0x01, 0x54, 0x77, 0x69, 0x17, 0x85, 0xD8, 0x0C, 0xA1, 0xBB, 0x7A, 0x0D, 0x93};
u8 c5[16] = { 0xFD, 0x2E, 0xF6, 0x92, 0xE4, 0x14, 0xFB, 0x2E, 0x93, 0xE3, 0x9C, 0x0A, 0x92, 0xD0, 0xE9, 0xAB};
u8 binArr[128];

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
    //
    // TEMP is a 128-bit value used within the computation of the functions.
    // TEMP = E[RAND XOR OP C ] K (while K is keysting)
    // OUT1 = E[TEMP XOR rot(IN1 XOR OPc , r1) XOR c1]k XOR OPc
    // r1=1F, r2= 3A, r3=01, r4=3F, r5=08

    // dummy values for SQN and AMF
    int i,j;
    u8 sqn[6]={ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
    u8 amf[2]={ 0x06, 0x07 };
    u8 in1[16];
    u8 dummy_rand[16];
    u8 dummy_k[16];
    u8 toEncrypt[16];
    u8 temp[16];
    u8* out1;
    out1 = malloc(16);

    printf("\nDUMMY_SQN: ");
    for (i = 0; i < 6; i++) {
        printf("%hhx", sqn[i]);
    }


    printf("\nDUMMY_AMF: ");
    for (i = 0; i < 2; i++) {
        printf("%hhx", amf[i]);
    }

    // create IN1
    for (i=0; i<6; i++) {
        in1[i] = sqn[i];
        in1[i+8] = sqn[i];
    }
    for (i=0; i<2; i++){
        in1[i+6] = amf[i];
        in1[i+14] = amf[i];
    }

    // print IN1
    printf("\nIN1: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", in1[i]);
    }

    // generate dummy RAND
    for (i = 0; i < 16; i++) {
        dummy_rand[i] = i;
    }

    // print dummy RAND
    printf("\nDUMMY_RAND: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", dummy_rand[i]);
    }
    printf("\nOPc:          ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", opc[i]);
    }

    for (i = 0; i < 16; i++) {
        toEncrypt[i] = dummy_rand[i] ^ opc[i];
        encrypt(toEncrypt, keyArr, temp);
    }

    printf("\r\nTEMP:         ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", temp[i]);
    }

    // generate most inner value for calculation of out1
    // TEMP XOR rot(IN1 XOR OPc , r1) XOR c1
    // r1=1F, r2= 3A, r3=01, r4=3F, r5=08
    for (i = 0; i < 16; i++) {
        out1[i] =  in1[i]^opc[i];
    }

    convertToBin(out1, binArr);
    rotWord(binArr, 128, 0x05); // replace with correct r1-value later
    
    printf("\nrotated Bits: ");
    for (i=0; i<128; i++){
        printf("%hhx", binArr[i]);
    }
    convertToHex(binArr, out1);

    printf("\nrotatedvalue: ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", out1[i]);
    }

    for (i = 0; i < 16; i++) {
        out1[i] = temp[i]^out1[i]^c1[i];
    }
    printf("\nxoredvalue : ");
    for (i = 0; i < 16; i++) {
        printf("%hhx", out1[i]);
    }

    // encrypt generated values
    encrypt(out1, keyArr, out1);

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

void convertToBin(u8* hexArr, u8* binArr) {
    int i,j;
    unsigned char mask = 1;
    
    for (j=0; j<16; j++){
        for (i = 0; i < 8; i++) {
            binArr[j*8 + i] = (hexArr[j] & (mask << (7-i))) != 0;
        }
    }
    printf("\narr converted: ");
    for (i=0; i<128; i++){
        printf("%hhx", binArr[i]);
    }
}

void convertToHex(u8* binArr, u8* hexArr){
    int i,j,k=0,temp,arrpos; // k iterates through binArr, i is for calculating each 8 bit to hex, j equals base for calculating hex values in each octet

    for (arrpos=0; arrpos<16; arrpos++){
        temp=0;
        j=128;
        for (i=0; i<8; i++){
            temp=temp+(binArr[k]*j);
            j=j/2;
            k++;
        }
        j=1;
        hexArr[arrpos]=temp;
    }
}