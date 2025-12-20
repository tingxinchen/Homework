#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include "Chain.h"

struct Term {
    int coef;
    int exp;
};

class Polynomial : public Chain<Term> {
public:
    Polynomial() : Chain<Term>() {}

    void NewTerm(int c, int e) {
        if (c == 0) return; // 係數為 0 不新增

        iterator prev = End();
        iterator cur = Begin();

        while (cur != End() && (*cur).exp > e) {
            prev = cur;
            ++cur;
        }

        if (cur != End() && (*cur).exp == e) {
            (*cur).coef += c;
            if ((*cur).coef == 0) { // 相加後係數為 0 → 刪除節點
                prev.GetNode()->link = cur.GetNode()->link;
                delete cur.GetNode();
            }
            return;
        }

        ChainNode<Term>* node = new ChainNode<Term>({ c, e });
        node->link = cur.GetNode();
        prev.GetNode()->link = node;
    }


    friend std::istream& operator>>(std::istream& in, Polynomial& p) {
        int n;
        in >> n;
        for (int i = 0; i < n; i++) {
            int c, e;
            in >> c >> e;
            p.NewTerm(c, e);
        }
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Polynomial& p) {
        bool first = true;  // 用來判斷是否為第一項

        for (auto it = p.Begin(); it != p.End(); ++it) {
            if ((*it).coef == 0) continue; // 跳過 0 項

            if (first) {
                // 第一項
                if ((*it).coef < 0) out << "-";
            }
            else {
                // 非第一項
                if ((*it).coef > 0) out << " + ";
                else out << " - ";
            }

            int absCoef = std::abs((*it).coef);

            // 如果係數為1且指數不為0，就省略 1
            if (!(absCoef == 1 && (*it).exp != 0))
                out << absCoef;

            // 指數部分
            if ((*it).exp != 0)
                out << "X^" << (*it).exp;

            first = false;
        }

        // 如果整個多項式都是0
        if (first) out << "0";

        return out;
    }
    Polynomial operator+(const Polynomial& rhs) const {
        Polynomial result;

        for (auto it = Begin(); it != End(); ++it)
            result.NewTerm((*it).coef, (*it).exp);

        for (auto it = rhs.Begin(); it != rhs.End(); ++it)
            result.NewTerm((*it).coef, (*it).exp);

        return result;
    }
    Polynomial(const Polynomial& p) : Chain<Term>() {
        for (auto it = p.Begin(); it != p.End(); ++it)
            NewTerm((*it).coef, (*it).exp);
    }

    Polynomial& operator=(const Polynomial& p) {
        if (this != &p) {
            Release();
            for (auto it = p.Begin(); it != p.End(); ++it)
                NewTerm((*it).coef, (*it).exp);
        }
        return *this;
    }

    ~Polynomial() {
        Release();
    }
};

#endif

