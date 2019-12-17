#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int N, d, e;
int initial();//1 ok, 0 notOK

int getPrime(int n);//取得第n個質數
int isPrime(int n);//判斷n是不是質數
int phi(int n);
int gcd(int a, int b);
int modInverse(int a, int n);//ax == 1 mod n
int mod(int a, int b);
int encrypt(int m, int e, int n);//計算 c = m^e mod n

int main()
{
    while(!initial());
    printf("Public Key (e, N): (%d, %d)\n", N, e);
    printf("Private key (d) : %d\n", d);

    char m[100];
    int myC[100];
    char myM[100];
    int len = 0;

    printf("\nInput your message:\n");
    while (scanf("%c", &m[len])!= EOF) {
        if (m[len]=='\n')
            break;
        len++;
    }
    m[len] = '\0';

    printf("The cyphertext is :\n");
    for (int i=0; i<len; i++) {
        myC[i] = encrypt(m[i], e, N);
        printf("%d ", myC[i]);
    }
    printf("\n");
    printf("\nplaintext after decryption:\n");
    for (int i=0; i<len; i++) {
        myM[i] = encrypt(myC[i], d, N);
        printf("%c", myM[i]);
    }
    printf("\n");

    return 0;
}

int initial()
{
    int p, q, phiN;
    //1-1 隨意選擇兩個大的質數p和q, p!=q, find N=q*p
    srand(time(NULL));
    p = getPrime(rand()%50+1);
    q = getPrime(rand()%50+1);
    while (p==q) {
        q = getPrime(rand()%50+1);
    }
    N = p*q;
    if (N <= 126) {
        return 0;
    }

    //1-2 取e, (e, phi(N))=1
    phiN = (p-1)*(q-1);
    do {
        e = rand()% phiN + 1;

    } while(gcd(phiN, e) != 1);

    //1-3 求d, ed = 1 mod phi(N)
    d = modInverse(e, phiN);
    int test = encrypt(126, e, N);
    if(encrypt(test, d, N)!=126) {
        return 0;
    }
    return 1;
}


int getPrime(int n)
{
    int cnt = 0;
    for (int i=2; cnt!=n; i++) {
        cnt+=isPrime(i);
        if (cnt == n)
            return i;
    }
    return -1;

}

int isPrime(int n)
{
    if (n == 1)
        return 0;
    if (n==2 || n==3 || n==5 || n==7)
        return 1;
    if (n%2 == 0)
        return 0;
    if (n%3 == 0)
        return 0;
    for (int i=2; i<n; i++) {
        if (n%i == 0)
            return 0;
    }
    return 1;
}

int phi(int n)
{
    int ans=0;
    for (int i=1; i<=n; i++) {
        if (n%i!=0)
            ans++;
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
      while (t[4]!= 1) {
        t[5] = t[1] - (t[3]*(t[2]/t[4]));
        t[6] = mod(t[2], t[4]);
        for (int i=1; i<=4; i++) {
            t[i] = t[i+2];
        }
      }
    return mod(t[3], n);

}

int mod(int a, int b)
{
    if (a < 0)
        return b + (a%b);
    else
        return (a%b);
}

int encrypt(int m, int e, int n)
{
    //計算 c = m^e mod n
    int ans = 1;
    for (int i=0; i<e; i++) {
        ans = (ans*m)%n;
     }

    return ans;
}
