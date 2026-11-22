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
CandArray arr;
IdTable ids;
SkillTable sk;
int activeCnt=0;
TNode*bst=0;
TNode*avl=0;
bool addCand(Candidate c){
    if(ids.find(c.id)!=-1)return false;
    c.active=true;
    int idx=arr.add(c);
    ids.put(c.id,idx);
    for(int i=0;i<c.sc;i++)sk.add(c.skills[i],idx);
    bst=bstInsert(bst,c.sal,idx);
    avl=avlInsert(avl,c.exp,idx);
    activeCnt++;
    return true;
}
bool removeCand(int id){
    int idx=ids.find(id);
    if(idx==-1)return false;
    Candidate&c=arr.data[idx];
    ids.remove(id);
    for(int i=0;i<c.sc;i++)sk.del(c.skills[i],idx);
    bst=bstDelete(bst,c.sal,idx);
    avl=avlDelete(avl,c.exp,idx);
    c.active=false;
    activeCnt--;
    return true;
}
TNode*newNode(int k,int i){TNode*n=new TNode;n->key=k;n->idx=i;n->h=1;n->l=0;n->r=0;return n;}
bool lessThan(int k1,int i1,int k2,int i2){return k1<k2||(k1==k2&&i1<i2);}
TNode*minNode(TNode*t){while(t->l)t=t->l;return t;}
int calcH(TNode*t){if(!t)return 0;int a=calcH(t->l);int b=calcH(t->r);return a>b?a+1:b+1;}
void freeTree(TNode*t){if(!t)return;freeTree(t->l);freeTree(t->r);delete t;}
bool treeSearch(TNode*t,int k,int i){
    while(t){
        cmpCount++;
        if(k==t->key&&i==t->idx)return true;
        t=lessThan(k,i,t->key,t->idx)?t->l:t->r;
    }
    return false;
}
TNode*bstInsert(TNode*t,int k,int i){
    if(!t)return newNode(k,i);
    if(lessThan(k,i,t->key,t->idx))t->l=bstInsert(t->l,k,i);
    else t->r=bstInsert(t->r,k,i);
    return t;
}
TNode*bstDelete(TNode*t,int k,int i){
    if(!t)return 0;
    if(k==t->key&&i==t->idx){
        if(!t->l){TNode*r=t->r;delete t;return r;}
        if(!t->r){TNode*l=t->l;delete t;return l;}
        TNode*m=minNode(t->r);
        t->key=m->key;t->idx=m->idx;
        t->r=bstDelete(t->r,m->key,m->idx);
    }
    else if(lessThan(k,i,t->key,t->idx))t->l=bstDelete(t->l,k,i);
    else t->r=bstDelete(t->r,k,i);
    return t;
}

int ht(TNode*t){return t?t->h:0;}
void upd(TNode*t){int a=ht(t->l);int b=ht(t->r);t->h=(a>b?a:b)+1;}
TNode*rotR(TNode*y){TNode*x=y->l;y->l=x->r;x->r=y;upd(y);upd(x);return x;}
TNode*rotL(TNode*x){TNode*y=x->r;x->r=y->l;y->l=x;upd(x);upd(y);return y;}
TNode*bal(TNode*t){
    upd(t);
    int b=ht(t->l)-ht(t->r);
    if(b>1){
        if(ht(t->l->l)<ht(t->l->r))t->l=rotL(t->l);
        return rotR(t);
    }
    if(b<-1){
        if(ht(t->r->r)<ht(t->r->l))t->r=rotR(t->r);
        return rotL(t);
    }
    return t;
}
TNode*avlInsert(TNode*t,int k,int i){
    if(!t)return newNode(k,i);
    if(lessThan(k,i,t->key,t->idx))t->l=avlInsert(t->l,k,i);
    else t->r=avlInsert(t->r,k,i);
    return bal(t);
}
TNode*avlDelete(TNode*t,int k,int i){
    if(!t)return 0;
    if(k==t->key&&i==t->idx){
        if(!t->l){TNode*r=t->r;delete t;return r;}
        if(!t->r){TNode*l=t->l;delete t;return l;}
        TNode*m=minNode(t->r);
        t->key=m->key;t->idx=m->idx;
        t->r=avlDelete(t->r,m->key,m->idx);
    }
    else if(lessThan(k,i,t->key,t->idx))t->l=avlDelete(t->l,k,i);
    else t->r=avlDelete(t->r,k,i);
    return bal(t);
}