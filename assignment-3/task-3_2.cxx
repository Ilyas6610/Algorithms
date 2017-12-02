/****************************************************************************
Задача 3_2. Порядковые статистики.

Дано число N и N строк. Каждая строка содержащит команду добавления или
удаления натуральных чисел, а также запрос на получение k-ой порядковой
статистики. Команда добавления числа A задается положительным числом A,
команда удаления числа A задается отрицательным числом "-A".
Запрос на получение k-ой порядковой статистики задается числом k.
Требуемая скорость выполнения запроса - O(log n).

  in    | out
  ----- | ---
  5     | 40
  40 0  | 40
  10 1  | 10
  4 1   | 4
  -10 0 | 50
  50 2  |

****************************************************************************/

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <algorithm>


using namespace std;

struct CNode {
    int Key;
    int Height;
    int Num;
    CNode* Left;
    CNode* Right;

    CNode( int key ): Key( key ), Height( 1 ), Left( NULL ), Right( NULL ), Num( 0 ) {}
};

void postOrder(CNode* root) {
    if (root) {
        postOrder(root->Right);
        cout << root->Key << ' ' << root->Num << endl;
        postOrder(root->Left);
    }
}

int Height( CNode* node ) {
    return node ? node->Height : 0;
}

int GetNum( CNode* node ) {
    return node ? node->Num + 1 : 0;
}

void Fix( CNode* node ) {
    node->Height = std::max( Height( node->Left ), Height( node->Right ) ) + 1;
}

CNode* RotateLeft ( CNode* node ) {
    CNode* right = node->Right;
    int r = GetNum( node->Left ) + GetNum( right->Left );
    int d = GetNum( node->Left ) + GetNum( node->Right );
    node->Right = right->Left;
    right->Left = node;
    right->Num = d;
    node->Num = r;
    Fix( node );
    Fix( right );
    return right;
}

CNode* RotateRight( CNode* node ) {
    CNode* left = node->Left;
    int r = GetNum( node->Right ) + GetNum( left->Right );
    int d = GetNum( node->Left ) + GetNum( node->Right);
    node->Left = left->Right;
    left->Right = node;
    left->Num = d;
    node->Num = r;
    Fix( node );
    Fix( left );
    return left;
}

int GetBalance ( CNode* node ) {
    return Height(node->Right) - Height(node->Left);
}

CNode* Balance ( CNode* node ) {
    Fix( node );
    int balance = GetBalance( node );
    if ( balance == -2 ) {
        if ( GetBalance( node->Left ) == 1 )
          node->Left = RotateLeft( node->Left );
      return RotateRight( node );
    }
    if ( balance == 2 ) {
        if ( GetBalance( node->Right ) == -1 )
            node->Right = RotateRight( node->Right );
        return RotateLeft( node );
    }
    return node;
}

CNode* Insert ( CNode* node, int key ) {
    if ( node == NULL ) {
        return new CNode( key );
    }
    node->Num++;
    if ( key < node->Key )
        node->Left = Insert( node->Left, key );
    else
        node->Right = Insert( node->Right, key );
    return Balance( node );
}

CNode* FindMin( CNode* node ) {
    if ( node->Left == NULL )
        return node;
    else
        return FindMin( node->Left);
}

CNode* RemoveMin( CNode* node ) {
    if ( node->Left == NULL )
        return node->Right;
    node->Num--;
    node->Left = RemoveMin( node->Left );
    return Balance( node );
}

CNode* Remove( CNode* node, int key ) {
    if ( node == NULL ) return NULL;
    node->Num--;
    if ( key < node->Key ){
        node->Left = Remove( node->Left, key );
    }
    else if ( key > node->Key ) {
        node->Right = Remove( node->Right, key );
    } else {
        CNode* left = node->Left;
        CNode* right = node->Right;
        delete node;
        if ( right == NULL )
            return left;
        CNode* min = FindMin( right );
        min->Right = RemoveMin( right );
        min->Left = left;
        min->Num = GetNum( min->Left ) + GetNum( min->Right );
        return Balance( min );
    }
    return Balance( node );
}


int KStat( CNode* root, int  k ){
    if( root == NULL )
            return -1;
    if( k == GetNum( root->Left ) )
        return root->Key;
    if( GetNum( root->Left ) >= k )
        KStat( root->Left, k );
    else
        KStat( root->Right, k - GetNum( root->Left ) - 1 );
}

int main() {
    int n, a, k;
    CNode *root = NULL;
    cin >> n;
    for( int i = 0; i < n; i++){
        cin >> a >> k;
        if ( a >= 0 )
            root = Insert( root, a );
        else
            root = Remove( root, abs( a ) ); 
    cout << KStat( root, k ) << endl;
    }

    return 0;
}
