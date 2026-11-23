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
struct TNode{int key;int idx;int h;TNode*l;TNode*r;};
TNode*newNode(int k,int i);
bool lessThan(int k1,int i1,int k2,int i2);
TNode*minNode(TNode*t);
int calcH(TNode*t);
void freeTree(TNode*t);
bool treeSearch(TNode*t,int k,int i);
TNode*bstInsert(TNode*t,int k,int i);
TNode*bstDelete(TNode*t,int k,int i);
int ht(TNode*t);
void upd(TNode*t);
TNode*rotR(TNode*y);
TNode*rotL(TNode*x);
TNode*bal(TNode*t);
TNode*avlInsert(TNode*t,int k,int i);
TNode*avlDelete(TNode*t,int k,int i);
struct HItem{double s;int exp;int id;int idx;};
bool better(const HItem&a,const HItem&b);
class Heap{
public:
    HItem*h;
    int n;
    Heap(HItem*a,int c);
    void down(int i);
    HItem pop();
};
void msort(HItem*a,HItem*t,int lo,int hi);

#endif