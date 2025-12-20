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

## 效能分析

## 測試與驗證

### 測試案例


### 編譯與執行指令
```cmd

```
### 結論


## 申論及開發報告
