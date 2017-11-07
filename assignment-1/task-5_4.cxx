//
// Решение предполагает использование стека.
// Способ реализации стека может быть любым (список/динамический массив).
//

/****************************************************************************

Задача 5_4. Вычисление выражения.

Дано выражение в инфиксной записи. Вычислить его, используя перевод
выражения в постфиксную запись. Выражение не содержит отрицительных
чисел.
Количество операций ≤ 100.

*Формат входных данных.* Строка, состоящая их символов
"0123456789-+/*()"

Гарантируется, что входное выражение корректно, нет деления на 0,
вычислимо в целых числах. Деление целочисленное.

*Формат выходных данных.* Значение выражения.

  in                      | out
  ------------------------|-----
  1 + 2                   | 3
  200-(123+34*2)+(48-2)   | 55

****************************************************************************/

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Stack {
public:
    Stack ( int size );
    ~Stack () { delete[] buffer; }

    void push(char x);
    char pop();
    void grow();
    //void print();
    char top();

private:
    char* buffer;
    int buffersize;
    int tail;
    int realSize;
};

Stack::Stack(int size) :
    buffersize ( size ),
    tail ( 0 ),
    realSize ( 0 )
{
    buffer = new char[buffersize];
};

void Stack::push(char x)
{
    if(realSize == buffersize)
        grow();
    buffer[tail] = x;
    tail++;
    realSize++;
};

char Stack::pop()
{
    if( realSize != 0 )
    {
        realSize--;
        return buffer[--tail];
    }
    else return -1;
};

char Stack::top()
{
    if( realSize != 0 )
        return buffer[tail - 1];
    else return 'a';
}

void Stack::grow()
{
    char* newBuffer = new char[buffersize*2];
    for(int i = 0; i < buffersize; i++)
        newBuffer[i] = buffer[i];
    delete[] buffer;
    buffer = newBuffer;
    buffersize = buffersize * 2;
};

int prior( char x )
{
    if( x == '(' ) return 4;
    else if( x == '+' || x == '-' ) return 2;
    else if( x == '*' || x == '/' ) return 3;
    else if( x == 'a' ) return 0;
}

int Split( string a, int *num, char *ch )
{
    string k = "";
    int i = 0;
    int d = 0;
    while( i != a.length() )
    {
        k = "";
        if( (a[i] == '+') || (a[i] == '-') || (a[i] == '/') || (a[i] == '*'))
        {
            ch[d] = a[i];
            d++;
            i++;
        }
        else if( a[i] == ' ' )
            while( a[i] == ' ' ) i++;
        while( a[i] != ' ' && ((a[i] != '+') && (a[i] != '-') && (a[i] != '/') && (a[i] != '*')))
        {
            if( i == a.length() ) break;
            k+=a[i];
            i++;
        }
        if( k != "" )
        {
            num[d] = stoi(k);
            d++;
        }
    }
    return d;
}

int main()
{
    string l, k;
    int m = 0;
    auto e = Stack(2);
    cin >> l;
    char *n = new char[l.size()*2];
    for( int i = 0; i < l.size(); i++)
    {
        if( l[i] == '+' || l[i] == '-' || l[i] == '/' || l[i] == '*' || l[i] == '(' || l[i] == ')' )
        {
            n[i + m]=' ';
            n[i + m + 1] = l[i];
            n[i + m + 2] = ' ';
            m+=2;
        }
        else
            n[i + m] = l[i];
    }
    n[l.size() + m] = '\0';
    e.push('a');
    for(int i = 0; i < l.size() + m; ++i)
    {
        if( (n[i] >= '0' && n[i] <= '9') || n[i] == ' ' )
            k+=n[i];
        else if( n[i] == ')' )
        {
            while( e.top() != '(' )
                k+=e.pop();
            e.pop();
        }

        else if( prior(n[i]) <= prior(e.top()) )
        {
            while ( prior(n[i]) <= prior(e.top()) )
            {
                if( e.top() == 'a' ) break;
                if(e.top() == '(') break;
                k+=e.pop();
            }
            e.push(n[i]);
        }
        else e.push(n[i]);
    };
    while(e.top() != 'a')
        k+=e.pop();
    int i = -1;
    delete []n;
    for(int i = 0; i < k.size(); i++ )
    {
        while( k[i] == ' '  && k[i + 1] == ' ')
            k.erase(k.begin() + i + 1, k.begin() + i + 2 );
    }
    int *num = new int[k.length()];
    for(int i = 0; i < k.length(); i++)
        num [i] = 0;
    char *ch = new char[k.length()];
    for(int i = 0; i < k.length(); i++)
        ch [i] = ' ';
    int lh = Split ( k, num, ch );
    int left, right;
    int j;
    for( int i = 0; i < lh ; i++ )
    {
        /*for(int j = 0; j < lh; j++)
            cout << num[j];
        cout << endl;*/
        if( ch[i] != ' ' )
        {
            left = 0, right = 0;
            for( int p = i; p >= 0; p-- )
            {
                if( num[p] != 0 && right == 0)
                {
                    right = num[p];
                    num[p] = 0;
                }
                else if( num[p] != 0 && left == 0)
                {
                    left = num[p];
                    num[p] = 0;
                    j = p;
                }
                if ( left != 0 && right != 0 )
                    break;
            };
            switch (ch[i])
            {
                case '+':
                    left += right;
                    ch[j] = ' ';
                    break;
                case '-':
                    left -= right;
                    ch[j] = ' ';
                    break;
                case '*':
                    left *= right;
                    ch[j] = ' ';
                    break;
                case '/':
                    left /= right;
                    ch[j] = ' ';
                    break;
            }
            num[j] = left;
        }
    };
    cout << num[0] << endl;
    delete []num;
    delete []ch;
    return 0;
};
