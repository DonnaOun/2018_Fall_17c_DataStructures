/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on October 25th, 2018, 4:55 PM
 * Purpose: Recursions
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
float fvRec(float,float,int);
float fv(float,float,int);
int gcd(int,int);
void relPrm(int,int,int&,int&,int&);
int mxRec(int *,int,int);
int mx(int *,int);
float expRec(int,int);
float exp(int,int);



//Execution Begins Here!
int main(int argc, char** argv) {
    //Utilize the rule of 72
    int nc=6;              //Number of Compounding periods years
    float ir=72/nc/100.0f; //Interest Rate %/year
    float pv=100;          //$100 in savings present value
    cout<<"Future Value Rec("<<pv<<","<<ir<<","<<nc<<")=$"
            <<fvRec(pv,ir,nc)<<endl;
    cout<<"Future Value    ("<<pv<<","<<ir<<","<<nc<<")=$"
            <<fv(pv,ir,nc)<<endl;
    
    //Test out gcd
    int num=343;
    int den=140;
    num=21;
    den=4;
    cout<<num<<"/"<<den<<"-> gcd = "<<gcd(num,den)<<endl;
    int a,b,c;
    relPrm(num,den,a,b,c);
    cout<<num<<"/"<<den<<" = "<<a<<" "<<b<<"/"<<c<<endl;

    //Test out max functions
    const int size=10;
    int aa[]={1,10,2,4,7,8,9,4,3,2};
    cout<<"Array Max = "<<mx(aa,size)
            <<" = "<<mxRec(aa,0,size)<<endl;
    
    //Test out the bloom filter expectation
    //Or sum an array filled randomly with 1's
    int n=365;//Example days in a year
    int k=2;//Number of hashes
    int m=14;//Number of dictionary elements
    cout<<"Expected Value = "
            <<expRec(k*m,n)<<" = "<<exp(k*m,n)<<endl;
    
    //Exit stage right!
    return 0;
}

float exp(int km,int n){
    return n*(1-pow(1-1.0f/n,km));
}

float expRec(int km,int n){
    if(km<=0)return 0;
    if(km==1)return 1;
    float val=expRec(km-1,n);
    return val+(n-val)/n;
}

int mx(int *a,int n){
    int max=a[0];
    for(int i=1;i<n;i++){
        if(max<a[i])max=a[i];
    }
    return max;
}

int mxRec(int *a,int beg,int end){
    //Base Case
    if(end-beg<=1)return a[beg];
    //Continue the split
    int half=(beg+end)/2;//Calculate the midpoint
    int m1=mxRec(a,beg,half);//return the max from first half
    int m2=mxRec(a,half,end);//return the max from second half
    return m1>m2?m1:m2;   //return the maximum of whole array
}

void relPrm(int nm,int dn,int&a,int&b,int&c){
    int gd=gcd(nm,dn);//Common factor
    nm/=gd;           //Reduce numerator
    c=dn/gd;          //Reduced denominator
    a=nm/c;          //Integer
    b=nm%c;          //New numerator
}

int gcd(int m,int n){
    //Base Case
    if(m==0)return n;
    if(m>n)return gcd(m%n,n);
    else return gcd(n%m,m);
}

float fvRec(float pv,float ir,int nc){
    //Base Case
    if(nc<=0)return pv;
    return fvRec(pv,ir,nc-1)*(1+ir);
}

float fv(float pv,float ir,int nc){
    //Loop
    for(int year=1;year<=nc;year++){
        pv*=(1+ir);
    }
    return pv;
}