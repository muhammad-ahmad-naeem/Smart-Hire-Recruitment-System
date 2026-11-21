#include "header.h"
long cmpCount = 0;
static unsigned int seed = 12345;
int rnd(int n)
{
    seed = seed * 1103515245u + 12345u;
    return (int)((seed >> 8) % (unsigned int)n);
}
int slen(const char *a)
{
    int n = 0;
    while (a[n])
        n++;
    return n;
}
void scopy(char *d, const char *s)
{
    int i = 0;
    while (s[i])
    {
        d[i] = s[i];
        i++;
    }
    d[i] = 0;
}
bool seq(const char *a, const char *b)
{
    int i = 0;
    while (a[i] && b[i])
    {
        if (a[i] != b[i])
            return false;
        i++;
    }
    return a[i] == b[i];
}
void lowerStr(char *s)
{
    for (int i = 0; s[i]; i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
}
void readWord(char *d, int mx)
{
    char ch;
    cin.get(ch);
    while (!cin.fail() && (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r'))
        cin.get(ch);
    int i = 0;
    while (!cin.fail() && ch != ' ' && ch != '\n' && ch != '\t' && ch != '\r')
    {
        if (i < mx - 1)
            d[i++] = ch;
        cin.get(ch);
    }
    d[i] = 0;
}
int readInt(const char *p, int lo, int hi)
{
    int x;
    while (true)
    {
        cout << p;
        cin >> x;
        if (cin.eof())
            return lo;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input" << endl;
            continue;
        }
        if (x >= lo && x <= hi)
            return x;
        cout << "Enter a value between " << lo << " and " << hi << endl;
    }
}
CandArray::CandArray(){cap=4;size=0;data=new Candidate[cap];}
CandArray::~CandArray(){delete[]data;}
int CandArray::add(const Candidate&c){
    if(size==cap){
        Candidate*t=new Candidate[cap*2];
        for(int i=0;i<size;i++)t[i]=data[i];
        delete[]data;
        data=t;
        cap*=2;
    }
    data[size]=c;
    return size++;
}
IdTable::IdTable(){for(int i=0;i<1009;i++)b[i]=0;}
IdTable::~IdTable(){
    for(int i=0;i<1009;i++){
        IdNode*c=b[i];
        while(c){IdNode*n=c->next;delete c;c=n;}
    }
}
int IdTable::h(int id){return id%1009;}
void IdTable::put(int id,int idx){
    IdNode*n=new IdNode;
    n->id=id;n->idx=idx;n->next=b[h(id)];
    b[h(id)]=n;
}
int IdTable::find(int id){
    IdNode*c=b[h(id)];
    while(c){
        cmpCount++;
        if(c->id==id)return c->idx;
        c=c->next;
    }
    return -1;
}
bool IdTable::remove(int id){
    IdNode*c=b[h(id)];
    IdNode*p=0;
    while(c){
        if(c->id==id){
            if(p)p->next=c->next;else b[h(id)]=c->next;
            delete c;
            return true;
        }
        p=c;c=c->next;
    }
    return false;
}
SkillTable::SkillTable(){for(int i=0;i<53;i++)b[i]=0;}
int SkillTable::h(const char*s){
    unsigned int x=5381;
    for(int i=0;s[i];i++)x=x*33+(unsigned char)s[i];
    return (int)(x%53);
}
SkNode*SkillTable::get(const char*s){
    SkNode*c=b[h(s)];
    while(c){if(seq(c->skill,s))return c;c=c->next;}
    return 0;
}
void SkillTable::add(const char*s,int idx){
    SkNode*c=get(s);
    if(!c){
        c=new SkNode;
        scopy(c->skill,s);
        c->n=0;c->cap=4;c->idx=new int[4];
        c->next=b[h(s)];
        b[h(s)]=c;
    }
    if(c->n==c->cap){
        int*t=new int[c->cap*2];
        for(int i=0;i<c->n;i++)t[i]=c->idx[i];
        delete[]c->idx;
        c->idx=t;
        c->cap*=2;
    }
    c->idx[c->n++]=idx;
}
void SkillTable::del(const char*s,int idx){
    SkNode*c=get(s);
    if(!c)return;
    for(int i=0;i<c->n;i++){
        if(c->idx[i]==idx){c->idx[i]=c->idx[c->n-1];c->n--;return;}
    }
}