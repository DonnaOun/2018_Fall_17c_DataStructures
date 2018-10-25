/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on October 24th, 2018, 11:20 AM
 * Purpose:  CPP Template
 *           To be copied for each project
 */

//System Libraries
#include <iostream> //I/O Library -> cout,endl
#include <iomanip>  //Format Library
#include <cmath>    //Math functions
using namespace std;//namespace I/O stream library created

//User Libraries

//Global Constants
//Math, Physics, Science, Conversions, 2-D Array Columns

//Function Prototypes
float rExp(int,int);   //recursive bloom filter sum
float rExpBad(int,int);//recursive bloom filter sum
float aExp(int,int);   //approximate bloom filter sum
float eExp(int,int);   //exact bloom filter sum
int gcd(int,int);      //greatest common divisor
float fv(float,float,int);//future value function
float fvReq(float,float,int);//future value function
int mx(int [],int,int);//Find a maximum in the array
int bCoeff(int,int);//Recursion for the binomial coefficients
int fib(int);
int fibRec(int);
double cosRec(double);
double sinRec(double);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare Variables
    int n=365;
    int km=28;
    int num=920,den=138,snum,sden;
    
    //Output for a comparison Bloop Filter
    cout<<"Bloom filter km="<<km<<" n="<<n<<endl;
    cout<<"Recursive     Bloom filter sum = "<<rExp(km,n)<<endl;
    //cout<<"Recursive Bad Bloom filter sum = "<<rExpBad(km,n)<<endl;
    cout<<"Approximate   Bloom filter sum = "<<aExp(km,n)<<endl;
    cout<<"Exact         Bloom filter sum = "<<eExp(km,n)<<endl;

    //Simplify a fraction
    int comFact=gcd(num,den);
    snum=num/comFact;
    sden=den/comFact;
    cout<<"The fraction "<<num<<"/"<<den
            <<" = "<<snum<<"/"<<sden<<endl;
    
    
    //Output the future value using the rule of 72
    float pv=100.0f;//$100
    float ir=0.06f;//6 percent
    int nc=0.72f/ir;//Rule of 72
    cout<<"Savings Function"<<endl;
    cout<<"Present Value = $"<<pv<<endl;
    cout<<"Interest Rate = "<<ir*100<<"%"<<endl;
    cout<<"Compounding Periods = "<<nc<<" years"<<endl;
    cout<<"Future Recursive Value = $"<<fvReq(pv,ir,nc)<<endl;
    cout<<"Future Value = $"<<fv(pv,ir,nc)<<endl;
    
    //Output the maximum value in an array
    int a[]={1,2,3,4,3,2};
    cout<<endl<<"Max value in the array = "<<mx(a,0,5)<<endl;
    
    //Output Pascal's Triangle
    cout<<endl<<endl;
    for(int row=0;row<=10;row++){
        for(int col=0;col<=row;col++){
            cout<<bCoeff(row,col)<<" ";
        }
        cout<<endl;
    }
    
    //Look at Fibonacci
    cout<<endl<<endl;
    cout<<fib(10)<<"="<<fibRec(10)<<endl;
    
    //Mutual Recursive Trig Functions
    cout<<endl<<endl;
    for(float alpha=-1;alpha<=1;alpha+=.1){
        cout<<"Sin("<<alpha<<")="
                <<sin(alpha)<<"="<<sinRec(alpha)<<endl;
    }
    cout<<endl<<endl;
    for(float alpha=-1;alpha<=1;alpha+=.1){
        cout<<"Cos("<<alpha<<")="
                <<cos(alpha)<<"="<<cosRec(alpha)<<endl;
    }
    
    //Exit program!
    return 0;
}

double cosRec(double angle){
    //Base Case
    double tol=1e-12f;
    if(abs(angle)<tol)return 1-angle*angle/2;
    //Recursive Call
    double a=cosRec(angle/2);
    double b=sinRec(angle/2);
    return a*a-b*b;
}

double sinRec(double angle){
    //Base Case
    double tol=1e-6f;
    if(abs(angle)<tol)return angle-angle*angle*angle/6;
    //Recursive Call
    double a=cosRec(angle/2);
    double b=sinRec(angle/2);
    return 2*a*b;
}

int fibRec(int n){
    //Base Conditions
    if(n==0)return 0;
    if(n==1)return 1;
    //Recursive Call
    return fib(n-1)+fib(n-2);
}

int fib(int n){
    //Base Conditions
    if(n==0)return 0;
    if(n==1)return 1;
    //Non-Recursive Call
    int cnt=2,fnm1=1,fnm2=0,fn;
    do{
        fn=fnm1+fnm2;
        fnm2=fnm1;
        fnm1=fn;
    }while(++cnt<n);
    return fn;
}

int bCoeff(int row,int col){
    //Base Conditions
    if(col==0)return 1;
    if(row==col)return 1;
    //Recursive Call
    return bCoeff(row-1,col-1)+bCoeff(row-1,col);
}

int mx(int a[],int beg,int end){
    if(end-beg<=1)return a[beg];
    int half=(beg+end)/2;
    int m1=mx(a,beg,half);
    int m2=mx(a,half,end);
    return (m1>m2?m1:m2);
}

float fvReq(float pv,float ir,int nc){
    if(nc<=0)return pv;
    return fv(pv,ir,nc-1)*(1+ir);
}

float fv(float pv,float ir,int nc){
    for(int i=1;i<=nc;i++){
        pv*=(1+ir);
    }
    return pv;
}

int gcd(int m,int n){
    if(m==0)return n;
    if(m>=n)return gcd(m%n,n);
    else return gcd(n%m,m);
}
float rExp(int km,int n){
    if(km<=0)return 0;
    if(km==1)return 1;
    float val=rExp(km-1,n);
    return val+(n-val)/n;
}
float rExpBad(int km,int n){
    if(km<=0)return 0;
    if(km==1)return 1;
    return rExpBad(km-1,n)+(n-rExpBad(km-1,n))/n;
}
float aExp(int km,int n){
    return n*(1-exp(-km/static_cast<float>(n)));
}
float eExp(int km,int n){
    return n*(1-pow((1-1.0f/n),km));
}