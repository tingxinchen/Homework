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

        if (first) cout << " "; // 空集合 ( )
        cout << ")";

        if (bit != total - 1) cout << ", ";
    }

    cout << "}" << endl;
}

int main()
{
    char S[20]; // 最多 20 個
    cout << "輸入集合元素（例如題目abc）: ";
    cin >> S;

    int n = strlen(S); // 輸入長度
    powerset(S, n);

    return 0;
}
