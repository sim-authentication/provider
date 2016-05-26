/* 
 * File:   milenage.h
 * Author: Marco Heumann
 *
 * Created on 26. März 2016
 */

#ifndef MILENAGE_H
#define MILENAGE_H
#endif /* MILENAGE_H */

typedef unsigned char u8;


void genRand(u8* mrand, u8* response_arr);
void f1(u8* keyArr, u8* mrand);
void f2_5(u8* keyArr, u8* response_arr);
void f5star(u8* keyArr, u8* sqn_ak);
void genAutn(u8* response_arr);