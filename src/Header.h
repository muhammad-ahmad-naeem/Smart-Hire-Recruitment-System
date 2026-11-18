#ifndef HEADER_H
#define HEADER_H
#include <iostream>
using namespace std;
extern long cmpCount;
int rnd(int n);
int slen(const char*a);
void scopy(char*d,const char*s);
bool seq(const char*a,const char*b);
void lowerStr(char*s);
void readWord(char*d,int mx);
int readInt(const char*p,int lo,int hi);
#endif