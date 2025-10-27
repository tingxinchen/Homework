# 41343128

作業二

## 解題說明

本題有兩個問題，問題一是做出一個多項式類別Polynomial，抽象資料還有私有成員，
問題二是寫C++函式以讀入與輸出多項式。函式應該多載運算子 << 與 >>，讓多項式能夠用直接的方式輸入與輸出。
### 輸入和輸出
第一行要輸入m和n，表示兩個多項是有多少係數，第二行要輸入多項式A的2m個數字，係數和指數的方式排列，第三行則是多項式B，也是輸入2n個。
### 解題策略
  1. Term：單項式，包含 coef（係數）與 exp（指數）。
  2. Polynomial：多項式，使用動態陣列 termsArray 儲存，記錄terms和capacity。
  3. newTerm若陣列滿了，擴充容量。
  4. (Add)相同指數:係數相加，非零加入結果；指數較大:將該項加入結果；剩下的加入結果。
  5. 輸入與輸出先讀入項數然後讀入係數和指數，依指數輸出，空多項式輸出 0。

## 程式實作

以下為主要程式碼：
```cpp
#include <iostream>
using namespace std;
class Polynomial; 
class Term {
    friend ostream& operator<<(ostream& os, const Polynomial& p);
    friend istream& operator>>(istream& is, Polynomial& p);
    friend class Polynomial;
private:
    float coef; // 係數
    int exp;    // 指數
};
class Polynomial {
    friend ostream& operator<<(ostream& os, const Polynomial& p);
    friend istream& operator>>(istream& is, Polynomial& p);
private:
    int capacity; 
public:
    int terms;    
    Term* termsArray;

    Polynomial();             
    Polynomial Add(Polynomial b); 
    void newTerm(float coef, int exp); 
};
Polynomial::Polynomial() {
    capacity = 10;
    terms = 0;
    termsArray = new Term[capacity];
}
void Polynomial::newTerm(float coef, int exp) {
    if (terms == capacity) { 
        capacity *= 2;
        Term* temp = new Term[capacity];
        for (int i = 0; i < terms; i++) temp[i] = termsArray[i];
        delete[] termsArray;
        termsArray = temp;
    }
    termsArray[terms].coef = coef;
    termsArray[terms].exp = exp;
    terms++;
}
Polynomial Polynomial::Add(Polynomial b) {
    Polynomial c;
    int aPos = 0, bPos = 0;

    while (aPos < terms && bPos < b.terms) {
        if (termsArray[aPos].exp == b.termsArray[bPos].exp) {
            float sum = termsArray[aPos].coef + b.termsArray[bPos].coef;
            if (sum != 0) c.newTerm(sum, termsArray[aPos].exp);
            aPos++; bPos++;
        }
        else if (termsArray[aPos].exp > b.termsArray[bPos].exp) {
            c.newTerm(termsArray[aPos].coef, termsArray[aPos].exp);
            aPos++;
        }
        else {
            c.newTerm(b.termsArray[bPos].coef, b.termsArray[bPos].exp);
            bPos++;
        }
    }

    for (; aPos < terms; aPos++)
        c.newTerm(termsArray[aPos].coef, termsArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.newTerm(b.termsArray[bPos].coef, b.termsArray[bPos].exp);

    return c;
}
istream& operator>>(istream& is, Polynomial& p) {
    int n;
    is >> n;
    for (int i = 0; i < n; i++) {
        float coef;
        int exp;
        is >> coef >> exp;
        p.newTerm(coef, exp);
    }
    return is;
}
ostream& operator<<(ostream& os, const Polynomial& p) {
    if (p.terms == 0) {  
        os << 0;
        return os;
    }
    for (int i = 0; i < p.terms; i++) {
        float coef = p.termsArray[i].coef;
        int exp = p.termsArray[i].exp;

        if (exp == 0) {
            os << coef;  
        }
        else if (exp == 1) {
            os << coef << "x";  
        }
        else {
            os << coef << "x^" << exp;
        }

        if (i != p.terms - 1) os << "+";
    }

    return os;
}

int main() {
    int m, n;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break; 
        Polynomial A, B, C;

        for (int i = 0; i < m; i++) {
            float coef; int exp;
            cin >> coef >> exp;
            A.newTerm(coef, exp);
        }
        for (int i = 0; i < n; i++) {
            float coef; int exp;
            cin >> coef >> exp;
            B.newTerm(coef, exp);
        }

        C = A.Add(B);
        cout << C << endl;
    }
    return 0;
}
```
## 效能分析

1. 時間複雜度：程式的時間複雜度為O(m+n)。
2. 空間複雜度：空間複雜度為O(m+n)。

## 測試與驗證

| 測試案例 | 多項式 A 輸入 | 多項式 B 輸入 | 預期輸出（A + B） | 實際輸出 |
|-----------|----------------|----------------|--------------------|-----------|
| 測試一 | `0` | `0` | `0` | `0` |
| 測試二 | `1x^2 + 2x + 1` | `0` | `1x^2 + 2x + 1` | `1x^2+2x+1` |
| 測試三 | `2x^2 + 3x + 1` | `x^2 + 2x + 3` | `3x^2 + 5x + 4` | `3x^2+5x+4` |
| 測試四 | `5x^3 + 2x + 1` | `3x^3 + 4x^2 + 7` | `8x^3 + 4x^2 + 2x + 8` | `8x^3+4x^2+2x+8` |
| 測試五 | `2x^2 + (-2x^2)` | `0` | `0` | `0` |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o polynomial polynomial.cpp
$ ./polynomial
6
```
### 結論


