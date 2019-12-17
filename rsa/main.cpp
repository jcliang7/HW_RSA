#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int getPrime(int n);//取得第n個質數
int isPrime(int n);//判斷n是不是質數
int phi(int n);
int gcd(int a, int b);
int modInverse(int a, int n);//ax == 1 mod n
int mod(int a, int b);
int N, d, e;
void inial();
int main()
{
    inial();
    printf("Public Key : (%d, %d)\n", N, e);
    printf("Private key : %d\n", d);
    return 0;
}

void inial()
{
     int p, q, phiN;
    //1.Initialization
    //1-1 隨意選擇兩個大的質數p和q, p!=q, find N=q*p
    srand(time(NULL));
    p = getPrime(rand()%500+1);
    q = getPrime(rand()%500+1);
    while (p==q)q = getPrime(rand()%500+1);
    //p=11;q=13;
    N = p*q;
    printf("p= %d, q=%d, N=%d\n", p, q, N);//can delete
    //1-2 取e, (e, phi(N))=1
    phiN = (p-1)*(q-1);
    printf("phi(N)=%d\n", phiN);//can delete
    do {
        e = rand()% phiN + 1;
    } while(gcd(phiN, e) != 1);
    //e=7;
    printf("e = %d\n", e);// can delete
    //1-3 求d, ed = 1 mod phi(N)
    d = modInverse(e, phiN);
    printf("d = %d\n", d);
    //1-4 public kye(N, e), private key d

}


int getPrime(int n)
{
    int cnt = 0;
    for (int i=2; cnt!=n; i++) {
        cnt+=isPrime(i);
        if (cnt == n)return i;
    }
    return -1;

}

int isPrime(int n)
{
    if (n == 1) return 0;
    if (n==2 || n==3 || n==5 || n==7) return 1;
    if (n%2 == 0) return 0;
    if (n%3 == 0) return 0;
    for (int i=2; i<n; i++) {
        if (n%i == 0) return 0;
    }
    return 1;
}

int phi(int n)
{
    int ans=0;
    for (int i=1; i<=n; i++) {
        if (n%i!=0)ans++;
    }
    return ans;
}

int gcd(int a, int b)
{
    while (b!=0) {
        int t = a%b;
        a = b;
        b = t;
    }
    return a;
}

int modInverse(int a, int n)
{
    int t[7] = {0, 0, n, 1, a, 0, 0};
    //printf("%2d * %2d = %3d mod %3d\n", a, t[1], t[2], n);//can delete
    //printf("%2d * %2d = %3d mod %3d\n", a, t[3], t[4], n);//can delete
    while (t[4]!= 1) {
        t[5] = t[1] - (t[3]*(t[2]/t[4]));
        t[6] = mod(t[2], t[4]);
        for (int i=1; i<=4; i++){
             t[i] = t[i+2];
        }
        //printf("%2d * %2d = %3d mod %3d\n", a, t[3], t[4], n);//can delete
    }
    return mod(t[3], n);

}

int mod(int a, int b)
{
    if (a < 0) return b + (a%b);
    else return (a%b);
}
