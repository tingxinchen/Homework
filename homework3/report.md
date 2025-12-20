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
    ChainNode<T>* header;  //頭節點

public:
    // 建構子
    Chain() {
        header = new ChainNode<T>(); // 新建header節點
        header->link = header;       // 空串列header指向自己
    }

    // 解構子
    ~Chain() {
        Release();
        delete header;
    }

    // 判斷串列是否為空
    bool IsEmpty() const {
        return header->link == header; 
    }

    // 取得第一個資料節點
    iterator Begin() const {
        return iterator(header->link);
    }

    // 結束
    iterator End() const {
        return iterator(header);
    }

    //插入新節點
    void InsertBack(const T& x) {
        ChainNode<T>* node = new ChainNode<T>(x); // 建立新節點
        // 找到最後一個節點
        ChainNode<T>* cur = header;
        while (cur->link != header) {
            cur = cur->link;
        }
        node->link = header; 
        cur->link = node;   
    }

    // 釋放所有節點記憶體
    void Release() {
        ChainNode<T>* cur = header->link;
        while (cur != header) {
            ChainNode<T>* temp = cur; // 暫存目前節點
            cur = cur->link;          // 移到下一個節點
            delete temp;              // 刪除節點
        }
        header->link = header;       // 釋放後重新指回header
    }
};
#
```
管理一串節點，提供新增、遍歷、釋放的功能，底層用 header 節點和循環鏈結串列。

`Polynomial.h`
```cpp
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

            // 如果係數1指數不為0
            if (!(absCoef == 1 && (*it).exp != 0))
                out << absCoef;

            // 指數部
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
```
Polynomial 類別提供：
1. 新增項目（NewTerm）
2. 多項式輸入/輸出（>> / <<）
3. 多項式加法（+）
4. 拷貝、指派、釋放記憶體（建構子、指派、解構子）

## 效能分析

## 測試與驗證

### 測試案例


### 編譯與執行指令
```cmd

```
### 結論


## 申論及開發報告
