/****************************************************************************
Задача 1_6.

Дан массив целых чисел A[0..n). Не используя других массивов
переставить элементы массива A в обратном порядке за O(n).
n ≤ 10000.

  in        | out
  ----------|----------
  4         | 2 -5 9 3
  3 9 -5 2  | 
****************************************************************************/

#include <iostream>

using namespace std;

int main()
{
    int a[10000], b;
    cin >> b;
    for(int i=0;i<b;i++)
        cin >> a[i];
    int d;
    if (b%2==0) d=b/2-1;
        else d=b/2;
    b--;
    for(int i=0;i<=d;i++)
    {
        int k=a[i];
        a[i]=a[b-i];
        a[b-i]=k;
    }
    for(int i=0;i<=b;i++)
        cout << a[i] << ' ';
    return 0;
}


