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
