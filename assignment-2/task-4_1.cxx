/****************************************************************************
 Задача 4_1. Первые k элементов длинной последовательности.

Дана очень длинная последовательность целых чисел длины n. Требуется вывести в отсортированном виде её первые k элементов. Последовательность может не помещаться в память. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.

in                 | out
------------------ | ---
9 4                | 1 2 3 4
3 7 4 5 6 1 15 4 2 |

****************************************************************************/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <limits.h>

using namespace std;

void Merge( const int* a, int aLen, const int* b, int bLen, int* c ) {
    int i = 0, j = 0;
    while( i < aLen && j < bLen ) {
        if( a[i] <= b[j] ) {
            c[i + j] = a[i];
            ++i;
        } else {
            c[i + j] = b[j];
            ++j;
        }
    }

    if( i == aLen ) {
        for( ; j < bLen; ++j )
            c[i + j] = b[j];
        } else {
        for( ; i < aLen; ++i )
            c[i + j] = a[i];
        }
};

void MergeSort( int* a, int aLen ) {
    if( aLen <= 1 ) {
        return;
    }
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    MergeSort( a, firstLen );
    MergeSort( a + firstLen, secondLen );
    int* c = new int[aLen];
    Merge( a, firstLen, a + firstLen, secondLen, c );
    memcpy( a, c, sizeof( int ) * aLen );
    delete[] c;
}

int main()
{
    int n, k = 0, m;
    cin >> n >> k;
    int* arr = new int[k];
    int* arr2 = new int[k];
    for( int i = 0; i < k; i++ )
        cin >> arr[i];
    MergeSort( arr, k );
    int i = k;
    while ( i < n )
    {
        int d = 0;
        while ( d < k && i < n)
        {
            cin >> arr2[d];
            d++;
            i++;
        };
        while ( d < k )
        {
            arr2[d] = INT_MAX;
            d++;
        };
        MergeSort( arr2, k );
        int p = k - 1, e = 0;
        while ( arr[p] >= arr2[e] )
        {
            swap( arr[p], arr2[e] );
            p--;
            e++;
        }
        MergeSort( arr, k );
    }
    for( int i = 0; i < k; i++ )
        cout << arr[i] << ' ';
    return 0;
}
