/****************************************************************************
Задача № 3. ДП (3 балла)

Дано N кубиков. Требуется определить каким количеством способов можно
выстроить из этих кубиков пирамиду.

*Формат входных данных:*
На вход подается количество кубиков N.

*Формат выходных данных:*
Вывести число различных пирамид из N кубиков.

****************************************************************************/

/****************************************************************************
Широкая пирамида.

Каждый вышележащий слой пирамиды должен быть строго меньше нижележащего.
N ≤ 300.

  ----+-----
  in  | out
  ----+-----
  3   | 2
  5   | 3
  7   | 5
  ----+-----

****************************************************************************/

#include <iostream>

using namespace std;

void PirWidth( long long** arr, int a ){
    for ( int i = 0; i < a * 2 + 1; i++ ) {
        for ( int k = 1; k <= i + 1; k++ ) {
            int n = i - k + 1;
            if ( n == 0 )
                arr[n][k]=1;
            else
            {
                arr[n][k] = 0;
                for ( int j = 1; j <= n; j++ ){
                    int i = n - j;
                    if ( j < k )
                        arr[n][k] += arr[i][j];
                }
            }
        }
    }
}

int main() {
	int a;
	cin >> a;
	long long **arr = new long long *[a * 2 + 1];
	for ( int i = 0; i < a * 2 + 1; i++ )
		arr[i] = new long long[a * 2 + 1];
    PirWidth( arr, a );
	cout << arr[a][a] + 1;
	for( int i = 0; i < a * 2 + 1; i++ )
        delete [] arr[i];
	delete []arr;
	return 0;
}
