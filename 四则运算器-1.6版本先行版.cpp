#include<iostream>
#include<string>
#include<windows.h>
using namespace std;
typedef long long ll;
string str;
bool is_sym(char ch){
    if(ch=='+' or ch=='-' or ch=='*' or ch=='/' or ch=='^')return true;
    else return false;
}
bool nf_sym1(string str){
    bool a1=false,a2=false;
    if(str.find('+')==string::npos)a1=true;
    if(str.find('-')==string::npos)a2=true;
    if(not a1)return false;
    if(not a2)return false;
    return true;
}
bool nf_sym2(string str){
    bool a1=false;
    if(str.find('*')==string::npos)a1=true;
    if(not a1)return false;
    return true;
}
namespace bigint{
    struct big{
        string num;
        void rev(){for(ll l=0,r=num.length()-1;l<r;l++,r--)swap(num[l],num[r]);}
        big(){num="";}
        big(string s){num=s;}
        ll size(){return num.length();}
        char operator[](ll kkk){return num[kkk];}
    };
    bool operator<(big a,big b){
        if(a.size()!=b.size())return a.size()<b.size();
        return a.num<b.num;
    }
    big operator+(big a,big b){
        if(a.size()<b.size())swap(a,b);
        ll jw=0;
        a.rev();b.rev();
        big ans;
        for(ll i=0;i<a.size();i++){
            ll tmp=a[i]+(i>=b.size()?0:b[i]-48)+jw-48;
            ans.num+=tmp%10+48;
            jw=tmp/10;
        }
        if(jw)ans.num+=jw+48;
        ans.rev();
        return ans;
    }
    big operator-(big a,big b){
        ll jw=0;
        a.rev();b.rev();
        big ans;
        for(ll i=0;i<a.size();i++){
            ll tmp=a[i]-(i>=b.size()?48:b[i])-jw;
            if(tmp<0){jw=1;tmp+=10;}
            ans.num+=(tmp+48);
        }
        ans.rev();
        return ans;
    }
    big operator*(big a,big b){
        a.rev();b.rev();
        big ans;
        ll re[100001],lc=a.size()+b.size();
        for(ll i=1;i<=a.size();i++){
            for(ll j=1;j<=b.size();j++)re[i+j-1]+=(a[i-1]-48)*(b[j-1]-48);
        }
        for(ll i=1;i<lc;i++){
            if(re[i]>9){re[i+1]+=re[i]/10;re[i]%=10;}
        }
        while(lc>1 and re[lc]==0)lc-=1;
        for(ll i=lc;i>=1;i--)ans.num+=re[i]+48;
        return ans;
    }
}
using namespace bigint;
string change1(string str){
    for(ll i=0;i<str.length();i++){
        if(str[i]=='*'){
            big a1,a2;
            ll j=i-1;
            while((not is_sym(str[j]))and(j>=0)){
                a1.num+=str[j];
                j-=1;
            }
            a1.rev();
            ll k=i+1;
            while((not is_sym(str[k]))and(k<str.length())){
                a2.num+=str[k];
                k+=1;
            }
            big res=a1*a2;
            j+=1;
            k-=1;
            string sstr=str.substr(j,k-j+1);
            str.replace(str.find(sstr),sstr.length(),res.num);
        }
    }
    return str;
}
string change2(string str){
    for(ll i=0;i<str.length();i++){
        if(str[i]=='+' or str[i]=='-'){
            big a1,a2;
            ll j=i-1;
            while((not is_sym(str[j]))and(j>=0)){
                a1.num+=str[j];
                j-=1;
            }
            a1.rev();
            ll k=i+1;
            while((not is_sym(str[k]))and(k<str.length())){
                a2.num+=str[k];
                k+=1;
            }
            big res;
            if(str[i]=='+')res=a1+a2;
            else res=a1-a2;
            j+=1;
            k-=1;
            string sstr=str.substr(j,k-j+1);
            str.replace(str.find(sstr),sstr.length(),res.num);
        }
    }
    return str;
}
string change(string str){
    while(nf_sym2(str)==false)str=change1(str);
    while(nf_sym1(str)==false)str=change2(str);
    return str;
}
string change4(string str){
    for(ll i=0;i<str.length();i++){
        if(str[i]=='('){
            ll start=i+1,end=i+1;
            while(str[end]!=')')end+=1;
            end-=1;
            string calc=str.substr(start,end-start+1);
            string ccalc=change(calc);
            calc='('+calc+')';
            str.replace(str.find(calc),calc.length(),ccalc);
        }
    }
    return str;
}
string cpr="Current version:1.5.3(The preview version for v1.6).Finished on 2021.8.30 21:08.\n" ;
string cpr1="Tips:This version does not support division and power calculation.\n\nThe mutiply calculation would be incorrect sometimes(the author is trying to fix it).\n";
string cpr2="Input 'exit' or 'quit' to end the program.\n";
void printcpr(string cpr){
	for(ll i=0;i<cpr.length();i++){
		cout<<cpr[i];
		Sleep(25);
	}
	cout<<"\n";
	return ;
}
void work(){
	if(str.find("/0")!=string::npos)cout<<"\nInvalid Input\n"; 
    while(str.find('(')!=string::npos)str=change4(str);
    str=change(str);
    cout<<"\nCalculation done.\n\n";
    cout<<"Result:"<<str<<"\n\n";
}
void runpro(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	printcpr(cpr);
	printcpr(cpr1);
	printcpr(cpr2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    cout<<"Please input...\n";
    cin>>str;
    while(str!="exit" and str!="quit"){
    	work();
    	cout<<"Please input...\n";
    	cin>>str;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	printcpr("This page will close within 60 seconds. Read or copy the result is available.\nThank you for using.\n");
    Sleep(60000);
}
int main(){
	runpro();
    return 0;
}
