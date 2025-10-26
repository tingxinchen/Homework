#include <iostream>
using namespace std;

class Polynomial; // 前置宣告

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
    int capacity; // 陣列容量
public:
    int terms;    // 實際項數
    Term* termsArray; // 存放 Term 的陣列

    Polynomial();                // 建構子
    Polynomial Add(Polynomial b); // 多項式相加
    void newTerm(float coef, int exp); // 新增項
};

//------------------ 建構子 ------------------
Polynomial::Polynomial() {
    capacity = 10;
    terms = 0;
    termsArray = new Term[capacity];
}

//------------------ 新增新項 ------------------
void Polynomial::newTerm(float coef, int exp) {
    if (terms == capacity) { // 若容量不足，自動擴大
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

//------------------ 加法 ------------------
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

    // 剩下的項直接加入
    for (; aPos < terms; aPos++)
        c.newTerm(termsArray[aPos].coef, termsArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.newTerm(b.termsArray[bPos].coef, b.termsArray[bPos].exp);

    return c;
}

//------------------ 輸入運算子 >> ------------------
istream& operator>>(istream& is, Polynomial& p) {
    int n;
    is >> n; // 讀取 n (有幾項)
    for (int i = 0; i < n; i++) {
        float coef;
        int exp;
        is >> coef >> exp;
        p.newTerm(coef, exp);
    }
    return is;
}

//------------------ 輸出運算子 << ------------------
ostream& operator<<(ostream& os, const Polynomial& p) {
    if (p.terms == 0) {  // 沒有任何項 → 輸出 0
        os << 0;
        return os;
    }
    for (int i = 0; i < p.terms; i++) {
        float coef = p.termsArray[i].coef;
        int exp = p.termsArray[i].exp;

        // 輸出係數
        if (exp == 0) {
            os << coef;  // 常數項
        }
        else if (exp == 1) {
            os << coef << "x";  // 一次項不顯示 ^1
        }
        else {
            os << coef << "x^" << exp;
        }

        // 項與項之間加 "+"
        if (i != p.terms - 1) os << "+";
    }

    // 額外輸出換行，照你的範例

    return os;
}

//------------------ 主程式 ------------------
int main() {
    int m, n;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break; // 可自行決定結束條件
        Polynomial A, B, C;

        // 讀入 A、B
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
