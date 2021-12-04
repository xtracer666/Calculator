#include<iostream>
#include<string>
#include<windows.h>
using namespace std;
typedef __int128 ll;
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
    bool a1=false,a2=false,a3=false;
    if(str.find('*')==string::npos)a1=true;
    if(str.find('/')==string::npos)a2=true;
    if(str.find('%')==string::npos)a3=true;
    if(not a1)return false;
    if(not a2)return false;
    if(not a3)return false;
    return true;
}
bool nf_sym3(string str){
	return str.find('^')==string::npos;
}
string ll_to_str(ll n){
    string ans;
    if(n==0)return "0";
    while(n){
        ans=char(n%10+48)+ans;
        n/=10;
    }
    return ans;
}
ll rev(ll n){
    ll ans=0;
    while(n){
        ans=ans*10+n%10;
        n/=10;
    }
    return ans;
}
string change1(string str){
    for(ll i=0;i<str.length();i++){
        if(str[i]=='*' or str[i]=='/' or str[i]=='%'){
            ll a1=0,a2=0;
            ll j=i-1;
            while((not is_sym(str[j]))and(j>=0)){
                a1=a1*10+str[j]-48;
                j-=1;
            }
            a1=rev(a1);
            ll k=i+1;
            while((not is_sym(str[k]))and(k<str.length())){
                a2=a2*10+str[k]-48;
                k+=1;
            }
            ll res;
            if(str[i]=='*')res=a1*a2;
            else if(str[i]=='/')res=a1/a2;
            else res=a1%a2;
            j+=1;
            k-=1;
            string sstr=str.substr(j,k-j+1);
            string ans=ll_to_str(res);
            str.replace(str.find(sstr),sstr.length(),ans);
        }
    }
    return str;
}
string change2(string str){
    for(ll i=0;i<str.length();i++){
        if(str[i]=='+' or str[i]=='-'){
            ll a1=0,a2=0;
            ll j=i-1;
            while((not is_sym(str[j]))and(j>=0)){
                a1=a1*10+str[j]-48;
                j-=1;
            }
            a1=rev(a1);
            ll k=i+1;
            while((not is_sym(str[k]))and(k<str.length())){
                a2=a2*10+str[k]-48;
                k+=1;
            }
            ll res;
            if(str[i]=='+')res=a1+a2;
            else res=a1-a2;
            j+=1;
            k-=1;
            string sstr=str.substr(j,k-j+1);
            string ans=ll_to_str(res);
            str.replace(str.find(sstr),sstr.length(),ans);
        }
    }
    return str;
}
ll fpow(ll x,ll y){
	if(y==1)return x;
	if(y==0)return 1;
	ll aaa=fpow(x,y>>1);
	aaa*=aaa;
	if(y&1)aaa*=x;
	return aaa;
}
string change3(string str){
    for(ll i=0;i<str.length();i++){
        if(str[i]=='^'){
            ll a1=0,a2=0;
            ll j=i-1;
            while((not is_sym(str[j]))and(j>=0)){
                a1=a1*10+str[j]-48;
                j-=1;
            }
            a1=rev(a1);
            ll k=i+1;
            while((not is_sym(str[k]))and(k<str.length())){
                a2=a2*10+str[k]-48;
                k+=1;
            }
            ll res=fpow(a1,a2);
            j+=1;
            k-=1;
            string sstr=str.substr(j,k-j+1);
            string ans=ll_to_str(res);
            str.replace(str.find(sstr),sstr.length(),ans);
        }
    }
    return str;
}
string change(string str){
	while(nf_sym3(str)==false)str=change3(str);
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
string cpr="Simple Calculator - Copyright @xtracer 2020   All rights reserved.\nThe 1.0 version was released on 2020.11.7";
string w="WARNING: ANY NUMBER EXCEEDED 2^127-1 WILL GET SOMETHING WRONG.";
string w1="WARNING 2: DO NOT TRY TO INPUT NUMBER(S) HEADED WITH 0.";
string cpr1="Current Version: 1.5.2\nFinished on 2021.12.04 10:56.\n";
string cpr2="Input 'exit' or 'quit' to end the program.\n";
void printcpr(string cpr){
	for(ll i=0;i<cpr.length();i++){
		cout<<cpr[i];
		Sleep(20);
	}
	cout<<"\n";
	return ;
}
void work(){
	if(str.find("/0")!=string::npos){cout<<"\nInvalid Input\n";return;} 
    while(str.find('(')!=string::npos)str=change4(str);
    str=change(str);
    cout<<"\nCalculation done.\n\n";
    cout<<"Result:"<<str<<"\n\n";
}
void runpro(){
	cout<<cpr<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	//printcpr(cpr);
	//printcpr(cpr1);
	printcpr(cpr2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	cout<<w<<endl<<endl<<w1<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),1|2|4);
    cout<<"Please input...\n";
    cin>>str;
    while(str!="exit" and str!="quit"){
    	work();
    	cout<<"Please input...\n";
    	cin>>str;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	system("pause");
}
int main(){
	runpro();
    return 0;
}
