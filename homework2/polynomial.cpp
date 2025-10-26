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
