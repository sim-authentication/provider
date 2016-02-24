#include <stdio.h>
#include <stdlib.h>

typedef u_int8_t u8;

void f1star();
void in1();
void temp_m();

void f1star(){
}

void in1(){
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

	printf("\n");
	printf("DUMMY_SQN: ");

	for (i=0; i<6; i++) {
		sqn[i] = i;
		printf("%x",sqn[i]);
	}

	printf("\n");
	printf("DUMMY_AMF: ");
	for (i=6; i<8; i++) {
		amf[i] = i;
		printf("%x",amf[i]);
	}

	// create IN1
	for (i=0; i<6; i++) {
		in1[i] = sqn[i];
		in1[i+8] = sqn[i];
	}
	for (i=0; i<2; i++) {
		in1[i+6] = amf[i];
		in1[i+14] = amf[i];
	}

	// print IN1
	printf("\n");
	printf("IN1: ");
	for (i=0; i<16; i++) {
		printf("%x", in1[i]);
	}
}

void temp_m() {
// TEMP is a 128-bit value used within the computation of the functions.
// TEMP = E[RAND XOR OP C ] K
	int i;
	u8 temp_m[16];

	// generate dummy RAND
	for (i=0; i<16; i++) {
		temp_m[i]=i;
	}

	// print dummy RAND
	printf("\n");
	printf("DUMMY_RAND: ");
	for (i=0; i<16; i++) {
		printf("%x",temp_m[i]);
	}
}