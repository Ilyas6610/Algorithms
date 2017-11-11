//
// Решение предполагает использование кучи.
//

/****************************************************************************
Задача 6_1. Жадина.

Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной
массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не
более K грамм. За раз он выбирает несколько самых тяжелых фруктов,
которые может поднять одновременно, откусывает от каждого половину и
кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм,
он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.

*Формат входных данных.* Вначале вводится n - количество фруктов и n
строк с массами фруктов. n ≤ 50000. Затем K - "грузоподъемность". K ≤ 1000.

*Формат выходных данных.* Неотрицательное число - количество подходов к
корзине.

  in             | out
  ---------------|-----
  3              | 4
  1 2 2          | 
  2              | 

  in             | out
  ---------------|-----
  3              | 5
  4 3 5          | 
  6              | 

  in             | out
  ---------------|-----
  7              | 3
  1 1 1 1 1 1 1  | 
  3              | 

****************************************************************************/

#include <iostream>
#include <cstring>
#include <array>
#include <assert.h>

using namespace std;

void SiftDown( int* arr, int n, int i )
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if( left < n && arr[left] > arr[i] )
        largest = left;
    if( right < n && arr[right] > arr[largest] )
        largest = right;
    if( largest != i ) {
        std::swap( arr[i], arr[largest] );
        SiftDown( arr, n, largest );
    }
}

void BuildHeap( int* arr, int n )
{
    for( int i = n / 2 - 1; i >= 0; --i ) {
        SiftDown( arr, n, i );
    }
}

void SiftUp( int* arr, int index )
{
    while( index > 0 ) {
        int parent = ( index - 1 ) / 2;
        if( arr[index] <= arr[parent] )
            return;
        std::swap( arr[index], arr[parent] );
        index = parent;
    }
}

void Add( int* arr, int n, int element )
{
    arr[n] = element;
    if ( n == 0 )
        return;
    SiftUp( arr, n - 1 );
}

int ExtractMax( int* arr, int n )
{
    int result = arr[0];
    arr[0] = arr[n];
    arr[n] = 0;
    if( n != 0 ) {
        SiftDown( arr, n, 0 );
    }
    return result;
}

void print( int* a, int n )
{
    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
}


int main ()
{
    int n, k, res = 0, r, sum;
    cin >> n;
    if ( n == 0 )
    {
        cout << 0;
        return 0;
    }
    int* a = new int[n];
    for(int i = 0; i < n; i++)
        cin >> a[i];
    cin >> k;
    int* b = new int[k];
    for ( int i = 0; i < k; i++ )
        b[i] = 0;
    BuildHeap( a, n );
    while( true )
    {
        sum = 0;
        r = 0;
        while( true )
        {
            int d = ExtractMax( a, n - 1 );
            n--;
            if( d == 0 )
            {
                n++;
                break;
            }
            if( sum + d <= k )
            {
                sum += d;
                b[r++] = d/2;
            }
            else
            {
                Add( a, n, d );
                n++;
                break;
            }
        };
        if ( sum != 0 )
            res++;
        for( int i = 0; i < r; i++ )
        {
            Add( a, n, b[i] );
            if ( b[i] != 0 )
                n++;
        };
        if ( a[0] == 0 )
            break;
    }
    cout << res;
    delete []a;
    delete []b;
    return 0;
}
