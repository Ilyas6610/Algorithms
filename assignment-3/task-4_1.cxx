/****************************************************************************
Задача 4_1.

Напишите две функции для создания архива из одного файла и извлечения файла из архива.

    // Метод архивирует данные из потока original
    void Encode(IInputStream& original, IOutputStream& compressed);

    // Метод восстанавливает оригинальные данные
    void Decode(IInputStream& compressed, IOutputStream& original);

где:

    typedef char byte;

    interface IInputStream {
        // Возвращает false, если поток закончился
        virtual bool Read(byte& value) = 0;
    };

    interface IOutputStream {
        virtual void Write(byte value) = 0;
    };

В архиве сохраняйте дерево Хаффмана и код Хаффмана от исходных данных.
Дерево Хаффмана требуется хранить эффективно - не более 10 бит на каждый 8-битный символ.

В контест необходимо отправить .cpp файл содержащий функции Encode, Decode, а также включающий файл Huffman.h. Тестирующая программа выводит размер сжатого файла в процентах от исходного.

Лучшие 3 решения из каждой группы оцениваются в 15, 10 и 5 баллов соответственно.

Пример минимального решения:

    #include "Huffman.h"

    static void copyStream(IInputStream&input, IOutputStream& output) {
        byte value;
        while(input.Read(value)) {
            output.Write(value);
        }
    }

    void Encode(IInputStream& original, IOutputStream& compressed) {
      copyStream(original, compressed);
    }

    void Decode(IInputStream& compressed, IOutputStream& original) {
        copyStream(compressed, original);
    }

****************************************************************************/

#include "Huffman.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

struct Node{
    Node(): Left( nullptr ), Right( nullptr ), isLeaf( false ) {};
    Node( char a, int b, bool c ):
        Key( a ),
        Amount( b ),
        isLeaf( c ),
        Right( nullptr ),
        Left( nullptr )
    {};
    Node( Node* a, Node* b ):
        Left( a ),
        Right( b ),
        isLeaf( false )
    {
        Amount = a->Amount + b->Amount;
    };
    ~Node(){
        delete Left;
        delete Right;
    }
    char Key;
    int Amount;
    bool isLeaf;
    Node* Left;
    Node* Right;
};

struct Comp{
    bool operator()( Node* a, Node* b ){
        return a->Amount < b->Amount;
    }
};

map<char, vector<char> > Code;
vector<char> Codes;
Node* root;

void CodeGen( Node* node ){

    if ( node->Left != nullptr ) {
        Codes.push_back('0');
        CodeGen( node->Left );
    }

    if ( node->Right != nullptr ){
        Codes.push_back('1');
        CodeGen( node->Right );
    }

    if ( node->isLeaf )
        Code.emplace( node->Key, Codes );

    Codes.pop_back();
}

int BitsAmount( int& l ){
    if( l >= 8 )
    {
        l -= 8;
        return 8;
    }
    else return l;
}

int Full = 0;

void Encode(IInputStream& original, IOutputStream& compressed) {
    byte value;
    vector<char> Buff;
    map<char, int> a;
    map<char, int>::iterator i;
    while(original.Read(value)) {
        Buff.push_back(value);
        a[value]++;
    }
    list<Node*> K;
    for( i = a.begin(); i != a.end(); i++ ){
        Node* node = new Node( i->first, i->second, true );
        K.push_back( node );
    };
    while( K.size() != 1 ){
        K.sort(Comp());

        Node* left = K.front();
        K.pop_front();

        Node* right = K.front();
        K.pop_front();

        Node* Parent = new Node( left, right );

        K.push_front( Parent );
    };
    root = K.front();
    K.pop_front();
    CodeGen( root );
    int n = 0;
    int l = 0;
    char s[8] = "";

    while( n != Buff.size() ){
        for( int j = 0; j < Code[Buff[n]].size(); j++ )
            Full++;
        n++;
    }
    n = 0;
    while( n != Buff.size() ){
        for( int j = 0; j < Code[Buff[n]].size(); j++ ){
            s[l] = Code[Buff[n]][j];
            l++;
            if( l == 8 || ( n == Buff.size() - 1 && j == Code[Buff[n]].size() - 1 ) ){
                char* c;
                int k = strtol(s, &c, 2);
                char m = (char)k;
                compressed.Write(m);
                for( int i = 0; i < 8; i++ )
                    s[i] = '\0';
                l = 0;
            }
        }
        n++;
    }
}

void Decode(IInputStream& compressed, IOutputStream& original) {
	Node *ptr = root;
	byte cur;
	int bits;
    while(compressed.Read(cur)) {
        bits = BitsAmount( Full );
        for (int i = bits - 1; i >= 0; i--){
            int bit = (cur >> i) & 1;
            if ( !bit )
                ptr = ptr->Left;
            else
                ptr = ptr->Right;

            if ( ptr->isLeaf ) {
                original.Write(ptr->Key);
                ptr = root;
            }
        }
    }
}
