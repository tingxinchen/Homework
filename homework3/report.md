# 41343128

作業三

## 解題說明

作業環狀鏈結串列，完成多項式的建立、輸入輸出與運算，
做出多項式的運算，並且能照指數由大到小排好。

每一個多項式項目包含三個：
- `coef`：係數
- `exp`：指數
- `link`：指向下一個節點的指標


### 解題策略
多項式以環狀鏈結串列表示，每個節點包含：
- `coef`：係數
- `exp`：指數
- `link`：指向下一個節點  

header 節點不存放實際資料，只作為串列起點與終點的判斷依據。

---

### Chain 與 ChainIterator 的設計
1. 使用 `Chain<T>` 來管理環狀鏈結串列。
2. 透過 `ChainIterator<T>`，讓串列可以使用陣列的方式運作：
   ```cpp
   for (auto it = poly.Begin(); it != poly.End(); ++it)
3.iterator 保存目前節點的指標，進行存取與移動。

## 程式實作
`ChainNode.h`
```cpp
#ifndef CHAINNODE_H
#define CHAINNODE_H

// 節點
template <class T>
class ChainNode {
public:
    T element;              
    ChainNode<T>* link;     // 指向下一個節點的指標

    // 建構子
    ChainNode(const T& e = T(), ChainNode<T>* l = nullptr) {
        element = e;       
        link = l;           // 將傳入的指標存到 link
    }
};

#endif
```
ChainNode提供單向鏈結串列節點模板，可用於任何的型態資料，並能方便地建立串列結構。

`ChainIterator.h`
```cpp
#ifndef CHAINITERATOR_H
#define CHAINITERATOR_H

#include "ChainNode.h"

// 迭代器
template <class T>
class ChainIterator {
private:
    ChainNode<T>* current;  // 目前節點的指標

public:
    // 建構子
    ChainIterator(ChainNode<T>* node = nullptr) {
        current = node;
    }

    // 取得目前節點的資料
    T& operator*() {
        return current->element;
    }

    // 取得節點本身
    ChainNode<T>* operator->() {
        return current;
    }

    //移動到下一個節點
    ChainIterator<T>& operator++() {
        current = current->link;
        return *this;
    }

    // 比較是否不同
    bool operator!=(const ChainIterator<T>& rhs) const {
        return current != rhs.current;
    }

    // 比較是否相同
    bool operator==(const ChainIterator<T>& rhs) const {
        return current == rhs.current;
    }

    // 取得目前節點的指標
    ChainNode<T>* GetNode() const {
        return current;
    }
};

#endif
```
節點儲存資料 + 下一個節點的指標，用來從頭到尾走訪鏈結串列。

`Chain.h`
```cpp
#ifndef CHAIN_H
#define CHAIN_H
#include "ChainNode.h"
#include "ChainIterator.h"

template <class T>
class Chain {
public:
    typedef ChainIterator<T> iterator;

protected:
    ChainNode<T>* header;

    static ChainNode<T>* avail;                   

    ChainNode<T>* getNode() {                   
        if (avail != nullptr) {
            ChainNode<T>* p = avail;
            avail = avail->link;
            return p;
        }
        return new ChainNode<T>();              
    }

    void retNode(ChainNode<T>* p) {             
        p->link = avail;
        avail = p;
    }

public:
    Chain() {
        header = getNode();                       
        header->link = header;
    }

    ~Chain() {
        Release();                                //  Release
        delete header;
    }

    bool IsEmpty() const {
        return header->link == header;
    }

    iterator Begin() const {
        return iterator(header->link);
    }

    iterator End() const {
        return iterator(header);
    }

    void InsertBack(const T& x) {
        ChainNode<T>* node = getNode();           
        node->element = x;                        
        node->link = header;

        ChainNode<T>* cur = header;
        while (cur->link != header) {
            cur = cur->link;
        }
        cur->link = node;
    }

    void Release() {
        if (header->link != header) {             
            ChainNode<T>* last = header->link;
            while (last->link != header) {
                last = last->link;
            }
            last->link = avail;
            avail = header->link;
        }
        header->link = header;
    }
};

template <class T>
ChainNode<T>* Chain<T>::avail = nullptr;

#endif
```
管理一串節點，提供新增、遍歷、釋放的功能，底層用 header 節點和循環鏈結串列。

`Polynomial.h`
```cpp
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <cmath>
#include "Chain.h"

struct Term {
    int coef;
    int exp;
};

class Polynomial : public Chain<Term> {
public:
    Polynomial() : Chain<Term>() {}

    void NewTerm(int c, int e) {
        if (c == 0) return;

        iterator prev = End();
        iterator cur = Begin();

        while (cur != End() && (*cur).exp > e) {
            prev = cur;
            ++cur;
        }

        if (cur != End() && (*cur).exp == e) {
            (*cur).coef += c;
            if ((*cur).coef == 0) { 
                prev.GetNode()->link = cur.GetNode()->link;
                delete cur.GetNode();
            }
            return;
        }

        ChainNode<Term>* node = getNode();         
        node->element = { c, e };                
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
        // 先計算有幾個非零項（因為 NewTerm 已經不會插入 coef==0）
        int n = 0;
        for (auto it = p.Begin(); it != p.End(); ++it) {
            n++;
        }

        // 輸出項數
        out << n;

        // 再逐項輸出 coef 和 exp
        for (auto it = p.Begin(); it != p.End(); ++it) {
            out << " " << (*it).coef << " " << (*it).exp;
        }

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
    Polynomial operator-(const Polynomial& rhs) const {
        Polynomial result;
        // 先把 this 的所有項加到 result
        for (auto it = Begin(); it != End(); ++it) {
            result.NewTerm((*it).coef, (*it).exp);
        }
        // 再把 rhs 的所有項用負係數加進去（就是減）
        for (auto it = rhs.Begin(); it != rhs.End(); ++it) {
            result.NewTerm(-(*it).coef, (*it).exp);
        }
        return result;
    }
    Polynomial operator*(const Polynomial& rhs) const {
        Polynomial result;
        // 對 this 的每一項
        for (auto it1 = Begin(); it1 != End(); ++it1) {
            // 和 rhs 的每一項相乘，產生新項加到 result
            for (auto it2 = rhs.Begin(); it2 != rhs.End(); ++it2) {
                int new_coef = (*it1).coef * (*it2).coef;
                int new_exp = (*it1).exp + (*it2).exp;
                result.NewTerm(new_coef, new_exp);
            }
        }
        return result;
    }
    float Evaluate(float x) const {
        float result = 0.0f;
        for (auto it = Begin(); it != End(); ++it) {
            // coef 是 int，轉成 float 計算
            result += static_cast<float>((*it).coef) * std::pow(x, (*it).exp);
        }
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
```
Polynomial 類別提供：
1. 新增項目（NewTerm）
2. 多項式輸入/輸出（>> / <<）
3. 多項式加法、減法、乘法
4. 多項式求值

## 效能分析
時間複雜度
1.加法與減法：O(m + n)
2.乘法：O(m × n)
3.輸入、輸出、求值：O(k)（k 是非零項數）
空間複雜度
每個多項式佔的空間：O(k)（k 是非零項數）

## 測試與驗證

### 測試案例
輸入一:\
多項式 a：3 5 3 -2 1 4 0（表示5x³ - 2x + 4）  \
多多項式 b：2 3 2 7 0 （表示 3x² + 7）\  
多輸出一:  \
多a + b → 4 5 3 3 2 -2 1 11 0 （5x³ + 3x² - 2x + 11）\
a - b → 4 5 3 -3 2 -2 1 -3 0 （5x³ - 3x² - 2x - 3）\
a(0) = 4.0000 （常數）\


輸入二:
多項式 a：2 3 2 1 0（表示3x² + 1）\
多項式 b：2 -3 2 5 1 （表示 -3x² + 5x）\
輸出二:\
a + b → 2 5 1 1 0 （5x + 1）\
a - b → 3 6 2 -5 1 1 0 （6x² - 5x + 1）\
### 編譯與執行指令
```cmd
g++ -std=c++17 -o poly main.cpp
```
### 結論
作業完成了一個用環狀鏈結串列來表示一元多項式的程式
程式可以做到：
1.讀入多項式（項數 n 後面接係數和指數）
2.輸出多項式時也用完全一樣的格式
3.自動把指數從大到小排好
4.加法、減法、乘法會自動合併同類項，如果係數變成 0 就自動刪掉那一項
5.提供求值功能，能算出多項式在某個 x 值時的結果

## 申論及開發報告
本次作業要求使用帶頭節點的環狀鏈結串列來實現一元多項式，節點包含係數、指數 與下一個節點指標。最初，我對環狀鏈結串列的概念還不熟，也忽略了輸入輸出必須完全相同的格式，以及記憶體回收的細節，所以一開始寫的程式有輸出錯成數學式。
輸出格式一開始用了數學表示3X^2 + 1，但題目指定要和輸入一樣的數字序列（項數 n 後接係數與指數）。後來我改成先數項數、再逐項輸出，才解決這個問題。
另外，題目要求補的減法、乘法和求值功能，一開始沒寫，我後來加進去。乘法會產生很多項，但用新增項的函數自動合併，就變簡單了。求值時把係數轉成浮點數計算，確保結果是正確的。
