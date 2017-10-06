/****************************************************************************
Задача 2_3.

Даны два строго возрастающих массива целых чисел A[0..n) и
B[0..m) и число k. Найти количество таких пар индексов (i, j), что
A[i] + B[j] = k. Время работы O(n + m). n, m ≤ 100000.

*Указание.* Обходите массив B от конца к началу.

  in             | out
  ---------------|-----
  4              | 3
  -5 0 3 18      | 
  5              | 
  -10 -2 4 7 12  | 
  7              | 

****************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int k, n, m, r;
    cin >> n;
    vector <int> a, b;
    for( int i = 0; i < n ; i++)
    {
        cin >> r;
        a.push_back(r);
    }
    cin >> m;
    for( int i = 0; i < m ; i++)
    {
        cin >> r;
        b.push_back(r);
    }
    cin >> k;
    m--;
    int p = 0, d = 0;
    while( p != n && m != -1)
    {
        if( m == -1 )
            m = 0;
        if( p == n )
            p = n-1;
        if( a[p] + b[m] > k)
            m--;
        else if( a[p] + b[m] < k)
            p++;
        else if( a[p] + b[m] == k)
        {
            d++;
            p++;
            m--;
        }
    }
    cout << d;
    return 0;
}

///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int bs(vector <int> r, int k, int n, int l)
{
    l--;
    if( !l )
        return r[n] > r[k] ? n : k ;
    int e;
    if( r[( k + n ) / 2] < r[( k + n ) / 2 + 1] )
        e = bs(r, ( k + n ) / 2 + 1, n, l);
    else
        e = bs(r, k, ( k + n ) / 2, l);
    return e;
}

int main()
{
    int n, d, k;
    vector <int> a;
    cin >> n;
    for( int i = 0; i < n ; i++)
    {
        cin >> k;
        a.push_back(k);
    };
    if( a[n - 1] > a [ n - 2 ])
    {
        cout << n - 1;
        return 0;
    }
    int r = log2(n);
    int e = bs(a, 0, n - 1, r + 1 );
    cout << e;
    return 0;
}
