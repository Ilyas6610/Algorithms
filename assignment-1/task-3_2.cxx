/****************************************************************************
Задача 3_2.

Дан массив целых чисел А[0..n-1]. Известно, что на интервале
[0, m] значения массива строго возрастают, а на интервале [m, n-1]
строго убывают. Найти m за O(log m).
2 ≤ n ≤ 10000.

  in                   | out
  ---------------------|-----
  10                   | 6
  1 2 3 4 5 6 7 6 5 4  | 

****************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int n, a[10000], d;
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> a[i];
    int k = log2(n);
    for(int i=2;i<=k;i++)
    {
        d =pow(2, i);
        if(d==n) d--;
        if(a[d-1]<a[d]) continue;
        else
        {
            while(a[d-1]>a[d])
                d--;
            cout << d;
            return 0;
        }
    }
    for(int i=d;i<n-1;i++)
    {
        if(a[i]>a[i+1])
        {
            cout << i;
            return 0;
        }
    }
    cout << n-1;
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
