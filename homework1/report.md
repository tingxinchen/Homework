# 41343128

作業一:problem1

## 解題說明

 problem1要求計算Ackermann函數，需要遞迴和非遞迴兩種做法。

### 解題策略
Ackermann 函數 \( A(m, n) \) 的數學定義如下：

$$
A(m, n) = 
\begin{cases} 
n + 1 & \text{if } m = 0 \\
A(m - 1, 1) & \text{if } n = 0 \\
A(m - 1, A(m, n - 1)) & \text{otherwise}
\end{cases}
$$

在遞迴寫法下:
1. 輸入數值m,n進入遞迴函式。
2. 會依照if條件判斷目前的狀況，並做出相對應的計算，當m=0時，回傳n+1。
3. 當最內層的遞迴結束，程式會依照順序繼續回傳結果。
4. 主程式收到函式的最後的回傳值，並將結果輸出。


在非遞迴寫法下:
1. 輸入數值m,n進入函式，並利用堆疊來模擬出遞迴時，存放資料的地方。
2. 使用while來操作堆疊，每次取出m,n最上層的堆疊判斷，直到堆疊清空。
3. 當m = 0時，計算n + 1並回傳結果。
4. 當 n = 0 時，將 (m - 1, 1) 推入堆疊，模擬遞迴呼叫 A(m - 1, 1)。
5. 當 m > 0 且 n > 0 時，依序將外層 (m - 1, ?) 與內層 (m, n - 1) 推入堆疊，模擬遞迴呼叫 A(m - 1, A(m, n - 1))。
6. 當堆疊中的所有計算完成後，函式回傳結果。

## 程式實作
以下為遞迴的主要程式碼：
```cpp
#include<iostream>
using namespace std;
int A(int m, int n) {
	if (m == 0) return n + 1;
	else if (n == 0) return A(m - 1, 1);
	else return A(m - 1, A(m, n - 1));
}

int main() {
	int m, n,end;
	cin >> m >> n;
	end=A(m, n);
	cout << end;
	return 0;
}
```
以下為非遞迴的主要程式碼：
```cpp
#include <iostream>
using namespace std;

int Ack(int m, int n)
{
    int stack_m[10000];
    int stack_n[10000];
    int top = 0;
    stack_m[top] = m;
    stack_n[top] = n;
    while (top >= 0)
    {
        m = stack_m[top];
        n = stack_n[top];
        top--;

        if (m == 0)     //n+1
        {
            n = n + 1;

            if (top < 0)
                return n; 

           
            stack_n[top] = n;
        }
        else if (n == 0)   //m-1,n=1
        {
            top++;
            stack_m[top] = m - 1;
            stack_n[top] = 1;
        }
        else    //m>0,n>0
        {
            //A(m-1, A(m, n-1))
            
            top++;
            stack_m[top] = m - 1; // 外層運算
            stack_n[top] = -1;    // 等待結果
            top++;
            stack_m[top] = m;     // 內層
            stack_n[top] = n - 1;
        }

        // 處理結果（-1 的地方）
        while (top >= 0 && stack_n[top] == -1)
        {
            stack_n[top] = n; // 用內層結果取代
        }
    }

    return n;
}


int main()
{
    while (true)
    {
        int m, n;
        cin >> m >> n;
        if (m == 0 && n == 0) break;
        cout << Ack(m, n) << endl;
    }
    return 0;
}

```

## 效能分析
遞迴:
1. 時間複雜度：O(A(m, n))，時間複雜度取決於輸入m和n值。
2. 空間複雜度：O(A(m, n))，空間複雜度取決於輸入m和n值。
非遞迴:
1. 時間複雜度：O(A(m, n))，時間複雜度取決於輸入m和n值。
2. 空間複雜度：O(1)（固定陣列大小）。

## 測試與驗證

### 測試案例
遞迴和非遞迴結果相同

| 測試案例 | 輸入參數 ($m$, $n$) | 預期輸出 $A(m,n)$ | 實際輸出 |
|----------|---------------------|-----------------|----------|
| 測試一   | (0, 0)              | 1               |1         |
| 測試二   | (0, 1)              | 2               |2         |
| 測試三   | (1, 0)              | 2               |2         |
| 測試四   | (1, 1)              | 3               |3         |
| 測試五   | (2, 2)              | 7               |7         |

### 編譯與執行指令
```cmd
$ g++ -std=c++17 -o ackermann_rec src/Ackermann.cpp
$ ./ackermann_rec
Enter m and n: 1 2
4
$ g++ -std=c++17 -o ackermann_non_rec src/Ackermann^'s_non-recursivecpp.cpp
$ ./ackermann_non_rec
Enter m and n: 1 2
4
```
### 結論
1. 程式能正確計算在範圍內的正確ackermann函數。  
2. 有遞迴和非遞迴版本。  
3. 較大輸入值，遞迴版本可能因堆疊溢出失敗，非遞迴版本受限於固定大小。

## 申論及開發報告
1. 用遞迴寫ackermann函數較簡單快速，透過遞迴呼叫三種不同狀況的執行方式，在程式的結構上相當整齊，是快速的方法。
2. 在非遞迴上，需要有地方來儲存還未計算的函數，所以需要用到堆疊，一開始我沒有想到堆疊也不熟悉，只想到字串，但字串不太好用來處理，所以上網找了很多非遞迴的寫法，有很多不同的方法，有些做法相當複雜，
參考到了一篇用堆疊的發現似乎相當好理解，也找了一些關於堆疊的語法，程式中利用堆疊來存放還未計算的值，例如A(1,3)->A(0,A(1,2))的地方，n的值還未出來要先存放，利用堆疊的操作為「先推入、後取出」的概念。
3. 非遞迴中的這段程式是，將內層計算的結果回填到上一層呼叫中，-1代表是為計算的標記。
   ```cpp
   while (top >= 0 && stack_n[top] == -1)
        {
            stack_n[top] = n; // 用內層結果取代
        }
   ```
# 41343128

作業一:problem2

## 解題說明

problem2 要求設計一個能輸出輸入集合 \( S \) 所有冪集的程式。

### 解題策略

一個集合若有 \( n \) 個元素，則它的子集合總數為 \( 2^n \)。  
可使用位元000-111的方式來表現出所有的子集合。



使用二進位：
- 每個子集合對應一個長度的二進位數字。
- 若第 \( i \) 位為 1，代表選取 \( S[i] \)；如果是0就不選取。
- 共有 \( 2^n \) 種組合，從 000到 111。

### 解題步驟

1. 使用 `strlen()` 取得輸入集合的長度。
2. 計算子集合的全部數量 。
3. 用 `for` 迴圈從 `0` 到 `total - 1` 每個可能的子集合。
4. 依照位元輸出每個子集合內容。
5. 空集合需要用 `( )`表示。

---

## 程式實作

```cpp
#include <iostream>
#include <cstring>  // for strlen()
using namespace std;

void powerset(char S[], int n)
{
    int total = 1 << n; // 2^n
    cout << "(S) = {";

    for (int bit = 0; bit < total; bit++)
    {
        cout << "(";
        bool first = true;

        for (int i = 0; i < n; i++)
        {
            if (bit & (1 << i))
            {
                if (!first) cout << ",";
                cout << S[i];
                first = false;
            }
        }

        if (first) cout << " "; // 空集合
        cout << ")";

        if (bit != total - 1) cout << ", ";
    }

    cout << "}" << endl;
}

int main()
{
    char S[20]; // 最多 20 個元素
    cout << "輸入集合元素（例如題目abc）: ";
    cin >> S;

    int n = strlen(S);
    powerset(S, n);

    return 0;
}
```
##效能分析

時間複雜度：

1. 時間複雜度 O(n × 2^n)。
2. 空間複雜度：使用固定大小的變數與陣列儲存輸入字元，空間複雜度 O(n)。

## 測試與驗證

### 測試案例
### 測試案例

| 測試案例 | 輸入集合| 預期輸出| 實際輸出 |
|-----------|---------------|---------------|-----------|
| 測試一 | a | {( ), (a)} | {( ), (a)} |
| 測試二 | ab | {( ), (a), (b), (a,b)} | {( ), (a), (b), (a,b)} |
| 測試三 | abc | {( ), (a), (b), (c), (a,b), (a,c), (b,c), (a,b,c)} | {( ), (a), (b), (c), (a,b), (a,c), (b,c), (a,b,c)} |








