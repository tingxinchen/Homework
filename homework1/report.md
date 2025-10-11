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






