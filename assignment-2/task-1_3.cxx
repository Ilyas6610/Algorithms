/****************************************************************************
Во всех вариантах данной задачи необходимо реализовать и использовать **сортировку вставками**.
****************************************************************************/

/****************************************************************************
Задача 1_3. Ломаная 2.

Аналогично 1.2, но ломаная должна быть замкнутая. Предполагается, что никакие три точки не лежат на одной прямой.

Указание: стройте ломаную от точки, имеющей наименьшую координату x.  Если таких точек несколько, то используйте точку с наименьшей координатой y.

Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех остальных точек.

in  | out
--- | ---
4   | 0 0
0 0 | 0 1
1 1 | 1 1
1 0 | 1 0
0 1 |

****************************************************************************/

#include <iostream>

using namespace std;

int main()
{
    int n, minx = 1313144, miny = 2421411, minnum = 2412421;
    cin >> n;
    int *x = new int[n+1];
    int *y = new int[n+1];
    double *angle = new double[n+1];
    for(int i=0;i<n;i++)
    {
        cin >> x[i] >> y[i];
    };
    for(int i=0;i<n;i++)
    {
        if(minx>x[i])
        {
            minx = x[i];
            miny = y[i];
            minnum = i;
        }
        else if(minx==x[i]&&miny>y[i])
        {
            miny = y[i];
            minnum = i;
        }
    };
    for(int i=0;i<n;i++)
    {
        if(minnum==i) continue;
        angle[i]=((double)(y[i]-y[minnum])/(double)(x[i]-x[minnum]));
    };
    for(int i=0;i<n-1;i++)
    {
        if(i==minnum) continue;
        for(int j=i+1;j<n;j++)
        {
            if(j==minnum) continue;
            if(angle[i]<angle[j])
            {
                swap(x[i],x[j]);
                swap(y[i],y[j]);
                swap(angle[i],angle[j]);
            }
        }
    };

    cout << x[minnum] << ' ' << y[minnum] << endl;
    for(int i=0;i<n;i++)
    {
        if(i==minnum) continue;
        cout << x[i] << ' ' << y[i] << endl;
    }
    delete []x;
    delete []y;
    delete []angle;
    return 0;
}

