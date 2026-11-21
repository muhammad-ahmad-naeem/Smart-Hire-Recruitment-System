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
struct Candidate{int id;char name[30];int exp;int edu;int sal;int sc;char skills[8][20];bool active;};
struct Job{char title[30];int minExp;int minEdu;int rc;char req[8][20];};
class CandArray{
public:
    Candidate*data;
    int size;
    int cap;
    CandArray();
    ~CandArray();
    int add(const Candidate&c);
};
struct IdNode{int id;int idx;IdNode*next;};
class IdTable{
public:
    IdNode*b[1009];
    IdTable();
    ~IdTable();
    int h(int id);
    void put(int id,int idx);
    int find(int id);
    bool remove(int id);
};
struct SkNode{char skill[20];int*idx;int n;int cap;SkNode*next;};
class SkillTable{
public:
    SkNode*b[53];
    SkillTable();
    int h(const char*s);
    SkNode*get(const char*s);
    void add(const char*s,int idx);
    void del(const char*s,int idx);
};

#endif