/****************************************************************************
Задача 1_5.

Вывести квадраты натуральных чисел от 1 до n, используя только
O(n) операций сложения и вычитания (умножением пользоваться нельзя).
n ≤ 1000.

  in  | out
  ----| -------------
  5   | 1 4 9 16 25
****************************************************************************/

#include <iostream>

using namespace std;

int main()
{
    int n,k=3,d=1;
    cin >> n;
    cout << 1 << ' ';
    for (int i=1;i<n;i++)
    {
        cout << d+k << ' ';
        d+=k;
        k+=2;
    }
    return 0;
}
