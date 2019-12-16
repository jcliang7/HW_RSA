# HW_RSA
## 數論與密碼學作業--RSA加密
[參考資料 https://en.wikipedia.org/wiki/RSA_(cryptosystem)](https://zh.wikipedia.org/wiki/RSA%E5%8A%A0%E5%AF%86%E6%BC%94%E7%AE%97%E6%B3%95)
## 2019/12/16

## 流程
### //1.Create public key and private key
    //1-1 隨意選擇兩個大的質數p和q, p!=q, find N=q*p
    //1-2 求r=phi(N);
    //1-3 選一個小於r的整數e, (e, r)=1
    //1-4 求d, ed = 1 mod r
