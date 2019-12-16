#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int getPrime(int n);//取得第n個質數
int isPrime(int n);//判斷n是不是質數
int phi(int n);
int gcd(int a, int b);
int main()
{
    int p, q, N, r;
    //1.Create public key and private key
    //1-1 隨意選擇兩個大的質數p和q, p!=q, find N=q*p
    srand(time(NULL));
    p = getPrime(rand()%500+1);
    q = getPrime(rand()%500+1);
    while (p==q)q = getPrime(rand()%500+1);
    p=3;q=5;
    N = p*q;
    printf("p= %d, q=%d, N=%d\n", p, q, N);
    //1-2 求r=phi(N);
    r = phi(N);
    printf("r=%d\n", r);
    //1-3 選一個小於r的整數e, (e, r)=1
    //1-4 求d, ed = 1 mod r
    return 0;
}

int getPrime(int n){
    int cnt = 0;
    for (int i=2; cnt!=n; i++){
        cnt+=isPrime(i);
        if (cnt == n)return i;
    }
    return -1;

}

int isPrime(int n){
    if (n == 1) return 0;
    if (n==2 || n==3 || n==5 || n==7) return 1;
    if (n%2 == 0) return 0;
    if (n%3 == 0) return 0;
    for (int i=2; i<n; i++){
        if (n%i == 0) return 0;
    }
    return 1;
}

int phi(int n)
{
    int ans=0;
    for (int i=2; i<=n; i++){
        if (gcd(n, i))ans++;
    }
    return ans;
}

int gcd(int a, b){
    int ans = 1;
    for (int i=2; i<=a; i++){
        if (a%i==0 && b%i==0)ans=i;
    }
    return ans;
}
