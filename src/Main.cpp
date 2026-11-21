#include "header.h"
int main(){
    while(true){
        cout<<endl<<"===== SmartHire ====="<<endl;
        cout<<"0. Exit"<<endl;
        int ch=readInt("Choice: ",0,13);
        if(ch==0)break;
    }
    return 0;
}
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