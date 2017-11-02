/****************************************************************************
Задача 6_1. Соревнование

**Быстрейшая сортировка.**

Дан массив целых чисел в диапазоне [0..10^9]. Размер массива кратен 10 и ограничен сверху значением 2.5 * 10^6 элементов. Все значения массива являются элементами псевдо-рандомной последовательности. Необходимо отсортировать элементы массива за минимальное время и вывести каждый **десятый** элемент отсортированной последовательности.

Реализуйте сортировку, основанную на QuickSort.

Минимальный набор оптимизаций, который необходимо реализовать:

1. Оптимизация ввода/вывода

2. Оптимизация выбора опорного элемента

3. Оптимизация Partition

4. Написать без рекурсии

5. Оптимизация концевой рекурсии

Задача обязательная.

За первое место в сдвоенной группе + 15 баллов.

За второе место + 10 баллов.

За третье место + 5 баллов.

in                   | out
-------------------- | ---
3 0 2 1 5 4 21 4 6 5 | 21

****************************************************************************/

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

void insertion_sort(int *a, int n) {
    for ( int i = 1; i < n ; ++i ) {
        int tmp = a[i];
        int j = i - 1;
        for ( ; j >= 0 && tmp < a[j]; --j )
            a[j + 1] = a[j];
        a[j + 1] = tmp;
    }
}

int med(int *a, int n)
{
    int b = 0;
    int last = a[n-1], middle = a[(b+n-1)/2], first = a[b];
    if(( first >= middle && first <= last ) || ( first <= middle && first >= last ))
    {
        return b;
    }
    else if(( last >= middle && last <= first ) || ( last <= middle && last >= first ))
    {
        return n-1;
    }
    else if(( first <= middle && middle <= last ) || ( first >= middle && middle >= last ))
    {
        return (b+n)/2;
    }
}

int partition(int *a, int n)
{
    int b = 0;
    int r = med(a, n);
    swap(a[r], a[b]);
    int i = n - 1, j = n - 1;
    while(j > b)
    {
        if( a[j] < a[b] ) j--;
        else
        {
            swap(a[j],a[i]);
            j--;
            i--;
        }
    };
    swap(a[i], a[b]);
    return i;
}

void qSort(int *a, int n) {
    if ( n < 25 ) {
        insertion_sort(a, n);
    } else {
        int part = partition(a, n);

        if( part > 0 )
            qSort(a, part);
        if( part + 1 < n )
            qSort(a + part + 1, n - (part  + 1));
    }
}

int main() {
    ios::sync_with_stdio(false);
    vector<int> data;
    int number;
    while ( cin >> number )
        data.push_back( number );
    int n = data.size();
    qSort( &data[0], n );
    for ( int i = 9; i < n; i += 10 ) cout << data[i] << ' ';
    return 0;
}
