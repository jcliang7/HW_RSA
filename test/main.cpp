#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int N, d, e;
int testp, testq;
int p, q, phiN;
void inial();

int getPrime(int n);//取得第n個質數
int isPrime(int n);//判斷n是不是質數
int phi(int n);
int gcd(int a, int b);
int modInverse(int a, int n);//ax == 1 mod n
int mod(int a, int b);
int encrypt(int m, int e, int n);//計算 c = m^e mod n
int main()
{
    FILE *pFile;
    pFile = fopen("output.txt", "w");

    if (NULL == pFile) {
        printf("open failure");
        return 1;
    } else {
        int cnt=1, phin;
        for (int i=1; i<=50; i++) {
            for (int j=1; j<50; j++) {
                if(i==j)
                    continue;
                phin = (i-1)*(j-1);
                if(phin <= 126 )
                    continue;

                e=2;
                do {
                    testp=i;
                    testq=j;
                    //1.Initialization
                    inial();
                    int test = encrypt(126, e, N);
                    int printAns =encrypt(test, d, N);
                    //printf("%d\n", printAns);
                    //if (encrypt(test, d, N) != 126) {
                    if (N>50000) {
                        /*
                        printf("#case %4d:\n", cnt);
                        printf("p= %d, q=%d, N=%d\n", p, q, N);//can delete
                        printf("phi(N)=%d\n", phiN);//can delete
                        printf("e = %d\n", e);// can delete
                        printf("d = %d\n", d);
                        printf("Public Key : (%d, %d)\n", N, e);
                        printf("Private key : %d\n", d);
                        // N = 143;
                        // d = 103;
                        // e=7;


                        printf("%d\n", test);
                        printf("%c\n", encrypt(test, d, N));
                        printf("=====================END=================\n");
                        */
                        fprintf(pFile, "#case %4d:\n", cnt);
                        fprintf(pFile, "p= %d, q=%d, N=%d\n", p, q, N);//can delete
                        fprintf(pFile, "phi(N)=%d\n", phiN);//can delete
                        fprintf(pFile, "e = %d\n", e);// can delete
                        fprintf(pFile, "d = %d\n", d);
                        fprintf(pFile, "Public Key : (%d, %d)\n", N, e);
                        fprintf(pFile, "Private key : %d\n", d);
                        fprintf(pFile, "%d\n", test);
                        fprintf(pFile, "%c\n", encrypt(test, d, N));
                        if (printAns == 126)fprintf(pFile, "equal to 126 : true\n");
                        else fprintf(pFile, "equal to 126 : false\n");
                        fprintf(pFile, "=====================END=================\n");
                    }
                    phin = (testp-1)*(testq-1);
                    cnt++;
                } while(e<phin);
            }
        }
    }
    fclose(pFile);
    return 0;
}

void inial()
{
    //int p, q, phiN;
    //1.Initialization
    //1-1 隨意選擇兩個大的質數p和q, p!=q, find N=q*p
    srand(time(NULL));
    p = getPrime(testp);
    q = getPrime(testq);
    N = p*q;
    // printf("p= %d, q=%d, N=%d\n", p, q, N);//can delete
    //1-2 取e, (e, phi(N))=1
    phiN = (p-1)*(q-1);
    //printf("phi(N)=%d\n", phiN);//can delete
    //e = 2;
    do {

        do {
            //e = rand()% phiN + 1;
            e++;
        } while(gcd(phiN, e) != 1);
        d = modInverse(e, phiN);
    } while(d > 100);
    //e=7;
    //e=5;
    //  printf("e = %d\n", e);// can delete
    //1-3 求d, ed = 1 mod phi(N)
    //d = modInverse(e, phiN);
    // printf("d = %d\n", d);
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
    //printf("%2d * %2d = %3d mod %3d\n", a, t[1], t[2], n);//can delete
    //printf("%2d * %2d = %3d mod %3d\n", a, t[3], t[4], n);//can delete
    while (t[4]!= 1) {
        t[5] = t[1] - (t[3]*(t[2]/t[4]));
        t[6] = mod(t[2], t[4]);
        for (int i=1; i<=4; i++) {
            t[i] = t[i+2];
        }
        //printf("%2d * %2d = %3d mod %3d\n", a, t[3], t[4], n);//can delete
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
        // printf("%d^%d = %d mod %d\n", m, i+1, ans, n);

    }

    return ans;
}
