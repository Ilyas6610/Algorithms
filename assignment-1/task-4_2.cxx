/****************************************************************************
Написать структуру данных, обрабатывающую команды push* и pop*.

*Формат входных данных.*
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back

Для очереди используются команды 2 и 3. Для дека используются все четыре команды.

Если дана команда pop*, то число b - ожидаемое значение.Если команда
pop вызвана для пустой структуры данных, то ожидается "-1".

*Формат выходных данных.*
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе,
если хотя бы одно ожидание не оправдалось, то напечатать NO.
****************************************************************************/

/****************************************************************************
Задача 4_2.

Реализовать дек с динамическим зацикленным буфером.

  in    | out
  ------|-----
  3     | YES
  1 44  | 
  3 50  | 
  2 44  | 

  in    | out
  ------|-----
  2     | YES
  2 -1  | 
  1 10  | 

  in    | out
  ------|-----
  2     | NO
  3 44  | 
  4 66  | 

****************************************************************************/

#include <iostream>
#include <cstdlib>
#include <vector>


class Deque {
public:
    Deque ( int size );
    ~Deque () { delete[] buffer; }

    void push_back(int x);
    void push_front(int x);
    int pop_back();
    int pop_front();
    void grow();
    void print();

private:
    int* buffer;
    int buffersize;
    int head;
    int tail;
    int realSize;
};

Deque::Deque(int size) :
    buffersize ( size ),
    head ( 0 ),
    tail ( 1 ),
    realSize ( 0 )
{
    buffer = new int[buffersize];
};

void Deque::push_back(int x)
{
    if(realSize == buffersize - 1)
        grow();
    //if(head != 0) tail++;
    buffer[tail] = x;
    tail = ( tail + 1 ) % buffersize;
    realSize++;
};

void Deque::push_front(int x)
{
    if(realSize == buffersize - 1)
        grow();
    //if(tail != 0) head = (head - 1 + buffersize) % buffersize;
    buffer[head] = x;
    head = (head - 1 +  buffersize) % buffersize;
    realSize++;
};

int Deque::pop_front()
{
    if( realSize != 0 )
    {
        realSize--;
        head = (head + 1) % buffersize ;
        return buffer[head];

    }
    else return -1;
};

int Deque::pop_back()
{
    if( realSize != 0 )
    {
        realSize--;
        tail = ( tail - 1 + buffersize ) % buffersize;
        return buffer[tail];
    }
    else return -1;
};

void Deque::grow()
{
    int* newBuffer = new int[buffersize*2];
    for(int i = tail; i > head - buffersize; --i)
        newBuffer[( i + buffersize * 2 ) % ( buffersize * 2 )] = buffer[( i + buffersize ) % buffersize ];
    delete[] buffer;
    buffer = newBuffer;
    buffersize = buffersize * 2;
    head = ( buffersize - ( buffersize / 2 - head));
    // else head = buffersize - (buffersize - tail);
};

void Deque::print()
{
    for( int i = 0; i < buffersize; i++ )
        std::cout << buffer[i] << ' ';
    std::cout << std::endl;
};

int main()
{
    int k, n, l, d;
    std::cin >> n;
    auto a = Deque(2);
    for(int i = 0; i < n; ++i)
    {
        std::cin >> k >> l;
        switch (k)
        {
            case 1:
                a.push_front(l);
                break;
            case 2:
                d = a.pop_front();
                if( d != l )
                {
                    std::cout << "NO";
                    return 0;
                };
                break;
            case 3:
                a.push_back(l);
                break;
            case 4:
                d = a.pop_back();
                if( d != l )
                {
                    std::cout << "NO";
                    return 0;
                };
                break;
        }
    }
    std::cout << "YES";
    return 0;
}
