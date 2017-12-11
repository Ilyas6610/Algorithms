/****************************************************************************
Жадные алгоритмы

**Заявки на переговоры.**

В большой IT-фирме есть только одна переговорная комната. Желающие
посовещаться заполняют заявки с желаемым временем начала и конца. Ваша
задача определить максимальное количество заявок, которое может быть
удовлетворено.

Число заявок ≤ 100000.

*Формат входных данных:*

Вход содержит только пары целых чисел --- начала и концы заявок.

*Формат выходных данных:*

Выход должен содержать натуральное число --- максимальное число заявок.

+------+-----+
| in   | out |
+------+-----+
| 1 2  | 5   |
| 2 5  |     |
| 7 10 |     |
| 2 3  |     |
| 6 7  |     |
| 4 7  |     |
| 3 6  |     |
| 3 5  |     |
| 1 2  |     |
| 4 5  |     |
+------+-----+
****************************************************************************/


#include <iostream>
#include <stdio.h>
#include <limits.h>

using namespace std;

void siftDown( int *a, int *b, int k, int N);

void swap(int *m, int *n)
{
	int tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;
}

void heapsort( int *a, int *b, int N){
	for ( int k = N/2; k >= 0; k-- )
		siftDown( a, b, k, N );

	while ( N-1 > 0 ) {
		swap( a[N-1], a[0] );
		swap( b[N-1], b[0] );
		siftDown( a, b, 0, N-1 );
		N--;
	}
}

void siftDown( int *a, int *b, int k, int N ){
	while ( k*2 + 1 < N ) {
 		int child = 2*k + 1;
		if ( ( child + 1 < N ) && ( a[child] < a[child+1] ) )
            child++;
		if ( a[k] < a[child] ) {
			swap( a[child], a[k] );
			swap( b[child], b[k] );
			k = child;
		}
		else
			return;
	}
}


int main()
{
    int n = 0, a[100000], b[100000], mn = -1, m = INT_MAX;
    while( !cin.eof() ){
        cin >> a[n] >> b[n];
        n++;
    };
    if( a[n] == 0 && b[n] == 0 )
        n--;
    heapsort( a, b, n );
    for( int i = 0; i < n; i++ )
        if( m > b[i] ){
            m = b[i];
            mn = i;
        };
    int e = 1, sum = 0;
    if( mn != -1 )
        sum++;
    for( int j = 0; j < n; j++ ){
        int k = INT_MAX;
        e = 0;
        for( int i = 0; i < n; i++ ){
            if( m <= a[i] && k > b[i] ){
                k = b[i];
                mn = i;
                e++;
            }
        }
        m = b[mn];
        if( e > 0 )
            sum++;
        if( e == 0 )
            break;
    };
    cout << sum;
    return 0;
}
