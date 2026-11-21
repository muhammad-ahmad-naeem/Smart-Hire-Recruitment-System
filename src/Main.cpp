#include "header.h"
const char*eduName(int e){return e==1?"Bachelors":e==2?"Masters":"PhD";}
void show(const Candidate&c){
    cout<<c.id<<" | "<<c.name<<" | exp "<<c.exp<<" yrs | "<<eduName(c.edu)<<" | salary "<<c.sal<<"k | skills:";
    for(int i=0;i<c.sc;i++)cout<<" "<<c.skills[i];
    cout<<endl;
}
bool dupSkill(char s[][20],int i){
    for(int j=0;j<i;j++)if(seq(s[j],s[i]))return true;
    return false;
}
void readSkills(char s[][20],int n){
    for(int i=0;i<n;i++){
        while(true){
            cout<<"Skill "<<i+1<<": ";
            readWord(s[i],20);
            lowerStr(s[i]);
            if(!dupSkill(s,i))break;
            cout<<"Duplicate skill"<<endl;
        }
    }
}
void readCand(Candidate&c){
    cout<<"Name (no spaces): ";
    readWord(c.name,30);
    c.exp=readInt("Years of experience (0-60): ",0,60);
    c.edu=readInt("Education (1=Bachelors 2=Masters 3=PhD): ",1,3);
    c.sal=readInt("Expected salary in thousands (1-10000): ",1,10000);
    c.sc=readInt("Number of skills (1-8): ",1,8);
    readSkills(c.skills,c.sc);
}
void addMenu(){
    Candidate c;
    c.id=readInt("Candidate ID (positive number): ",1,2000000000);
    if(ids.find(c.id)!=-1){cout<<"ID already exists"<<endl;return;}
    readCand(c);
    addCand(c);
    cout<<"Candidate added"<<endl;
}
void updateMenu(){
    Candidate c;
    c.id=readInt("Candidate ID: ",1,2000000000);
    if(ids.find(c.id)==-1){cout<<"Candidate not found"<<endl;return;}
    readCand(c);
    removeCand(c.id);
    addCand(c);
    cout<<"Candidate updated"<<endl;
}
void deleteMenu(){
    int id=readInt("Candidate ID: ",1,2000000000);
    if(removeCand(id))cout<<"Candidate deleted"<<endl;
    else cout<<"Candidate not found"<<endl;
}
void searchId(){
    int id=readInt("Candidate ID: ",1,2000000000);
    int idx=ids.find(id);
    if(idx==-1)cout<<"Candidate not found"<<endl;
    else show(arr.data[idx]);
}
void searchSkill(){
    char s[20];
    cout<<"Skill: ";
    readWord(s,20);
    lowerStr(s);
    SkNode*nd=sk.get(s);
    if(!nd||nd->n==0){cout<<"No candidates have this skill"<<endl;return;}
    for(int i=0;i<nd->n;i++)show(arr.data[nd->idx[i]]);
    cout<<nd->n<<" candidate(s) found"<<endl;
}
void listAll(){
    for(int i=0;i<arr.size;i++)if(arr.data[i].active)show(arr.data[i]);
    cout<<"Total candidates: "<<activeCnt<<endl;
}
int main(){
    while(true){
        cout<<endl<<"===== SmartHire ====="<<endl;
        cout<<"1. Add candidate"<<endl;
        cout<<"2. Update candidate"<<endl;
        cout<<"3. Delete candidate"<<endl;
        cout<<"4. Search by ID (hash table)"<<endl;
        cout<<"5. Search by skill (hash table)"<<endl;
        cout<<"6. List all candidates (dynamic array)"<<endl;
        cout<<"0. Exit"<<endl;
        int ch=readInt("Choice: ",0,13);
        if(ch==0)break;
        else if(ch==1)addMenu();
        else if(ch==2)updateMenu();
        else if(ch==3)deleteMenu();
        else if(ch==4)searchId();
        else if(ch==5)searchSkill();
        else if(ch==6)listAll();
    }
    return 0;
}