/****************************************************************************

Задача 5_2. LSD для long long.

Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106. Отсортировать массив методом поразрядной сортировки LSD по байтам.

in          | out
----------- | ---
3           | 4 7 1000000
4 1000000 7 |

****************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void CountingSort( long long* a, int n, long long* b ) {
    const int k = 10;
    int* c = new int[k];
    long long* d = new long long[n];
    for( int i = 0; i < k; ++i )
        c[i] = 0;
    for( int i = 0; i < n; ++i ){
        d[i] = b[i]%10;
        //cout << d[i] << endl;
        c[d[i]]++;
        b[i]/=10;
    };
    long long* e = new long long[n];
    long long* l = new long long[n];
    int r = 0;
    for( int i = 0; i < k; ++i )
    {
        for( int j = 0; j < n; ++j )
        {
            if( c[i] == 0 ) break;
            if( d[j] == i )
            {
                e[r] = a[j];
                l[r] = b[j];
                r++;
                c[i]--;
            };
        }
    };
    for( int i = 0; i < n; i++ )
    {
        a[i] = e[i];
        b[i] = l[i];
    };
    delete []l;
    delete []c;
    delete []e;
    delete []d;
};

void LSDSort( long long* a, int n, long long* b, int m ) {
    for( int r = 0; r < m; ++r )
        CountingSort( a, n, b );
}

int main()
{
    long long n, k = 0, maxL = 0;
    cin >> n;
    long long* a = new long long[n];
    long long* b = new long long[n];
    for( int i = 0; i < n; i++ )
    {
        cin >> a[i];
        b[i] = a[i];
        if( k < a[i] ) k = a[i];
    }
    while ( k != 0 )
    {
        k/=10;
        maxL++;
    };
    LSDSort( a, n, b, maxL );
    for( int i = 0; i < n; i++ )
        cout << a[i] << ' ';
    delete []b;
    delete []a;
    return 0;
}

