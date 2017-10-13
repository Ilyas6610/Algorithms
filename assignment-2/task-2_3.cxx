/****************************************************************************
Во всех задачах данного раздела необходимо реализовать и использовать **локальную пирамидальную сортировку** (без использования дополнительной памяти). Общее время работы алгоритма O(n log n).
****************************************************************************/

/****************************************************************************
Задача 2_3. Закраска прямой 1.

На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.

in  | out
--- | ---
3   | 5
1 4 |
7 8 |
2 5 |

****************************************************************************/

#include <iostream>
#include <algorithm>

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
	for (int k = N/2; k >= 0; k--) {
		siftDown( a, b, k, N);
	}

	while (N-1 > 0) {
		swap(a[N-1], a[0]);
		swap(b[N-1], b[0]);
		siftDown(a, b, 0, N-1);
		N--;
	}
}

void siftDown( int *a, int *b, int k, int N){
	while ( k*2 + 1 < N ) {
 		int child = 2*k + 1;
		if ((child + 1 < N) && (a[child] < a[child+1])) child++;
		if (a[k] < a[child]) {
			swap( a[child], a[k] );
			swap(b[child], b[k]);
			k = child;
		}
		else
			return;
	}
}

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n*2];
    int *a = new int[n*2];
    for(int i=0;i<n*2;i++)
    {
        cin >> arr[i];
        if(i%2==0) a[i] = 1;
        else a[i]=-1;
    };
    heapsort(arr,a,n*2);
    int d=0, open=0, res=0;
    for(int i=0;i<n*2;i++)
    {
        d+=a[i];
        if(d==0&&i!=0)
        {
            res=res + (arr[i] - arr[open]);
            open=i+1;
        };
    };
    cout << res;
    delete []a;
    delete []arr;
    return 0;
}
