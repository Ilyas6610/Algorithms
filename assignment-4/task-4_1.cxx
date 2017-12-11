/****************************************************************************
Задача № 4. Динамика на дереве (6 баллов)

Дано невзвешенное дерево. Расстоянием между двумя вершинами будем
называть количество ребер в пути, соединяющем эти две вершины.

****************************************************************************/

/****************************************************************************

Самая удаленная вершина.

Для каждой вершины определите расстояние до самой удаленной от нее
вершины. Время работы должно быть O(n).

*Формат входных данных:*

В первой строке записано количество вершин n ≤ 10000. Затем следует n --
1 строка, описывающая ребра дерева. Каждое ребро -- это два различных
целых числа -- индексы вершин в диапазоне [0, n-1]. Индекс корня -- 0.
В каждом ребре родительской вершиной является та, чей номер меньше.

*Формат выходных данных:*

Выход должен содержать n строк. В i-ой строке выводится расстояние от
i-ой вершины до самой удаленной от нее.

+-----+-----+
| in  | out |
+-----+-----+
| 3   | 2   |
| 0 1 | 1   |
| 1 2 | 2   |
+-----+-----+

****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

struct Node{
    Node( int _Pos, int _Depth ):
        Pos( _Pos ),
        Depth( _Depth ),
        Max( 0 ),
        Max2( 0 )
    {};
    ~Node();
    int Pos;
    int Depth;
    int Max;
    int Max2;
    Node* Parent;
    vector<Node*> Children;
};

void Add( Node* root ,int parent, int child ){
    if( root->Pos == parent ){
        Node* c = new Node( child, root->Depth + 1 );
        c->Parent = root;
        root->Children.push_back( c );
        return;
    } else
        for( int i = 0; i < root->Children.size(); i++ )
            Add( root->Children[i], parent, child );
}

pair<int, int> DFS( Node* root, int &max_depth, int &max_pos ){
    for( int i = 0; i < root->Children.size(); i++ )
        DFS( root->Children[i], max_depth, max_pos );
    if( root->Depth > max_depth ){
        max_depth = root->Depth;
        max_pos = root->Pos;
    }
    pair<int, int> k = { max_depth, max_pos };
    return k;
}

void max_parent( Node* root, const int &max_pos, int &k ){
    for( int i = 0; i < root->Children.size(); i++ ){
        if( k != 0 )
            return;
        max_parent( root->Children[i], max_pos, k );
    }
    if( root->Pos == max_pos ){
        while( root->Parent->Pos != 0 )
            root = root->Parent;
        k = root->Pos;
    }
}

void maxChild( Node *root, int k, int r, int &m ){
    for( int i = 0; i < root->Children.size(); i++ ){
        if( root->Children[i]->Pos == k ){
            continue;
        }
        maxChild( root->Children[i], k, r + 1, m );
    }
    if ( r > m )
        m = r;
}

void maxTree( Node* root, const int &max_pos, int &k, const int maxF, const int maxS ){
    for( int i = 0; i < root->Children.size(); i++ ){
        if( k != 0 )
            return;
        maxTree( root->Children[i], max_pos, k, maxF, maxS );
    }
    if( root->Pos == max_pos ){
        vector <int> r;
        while( root->Pos != 0 ){
            r.push_back( root->Pos );
            root = root->Parent;
        }
        int k = r.size() - 1;
        while( k != 0 ){
            for( int i = 0; i < root->Children.size(); i++ ){
                if( root->Children[i]->Pos == r[k] ){
                    int d = 0;
                    root = root->Children[i];
                    k--;
                    maxChild( root, r[k], 0, d );
                    root->Max2 = d;
                    if( root->Parent->Max2 > root->Max2 && ( root->Parent->Max2 != 0 || root->Parent == 0 ) )
                        root->Max2 = root->Parent->Max2 + 1;
                    root->Max = max( max ( root->Depth + maxS, root->Parent->Max2 + 1 ), max( maxF - root->Depth, d ) );
                }
            }
        }
        k = root->Pos;
    }
}

void MaxDepthV1( Node* root, const int d, const int k ){
    root->Max = root->Depth + d;
    for( int i = 0; i < root->Children.size(); i++ ){
        if( root->Children[i]->Pos == k )
            continue;
        MaxDepthV1( root->Children[i], d, k );
    }
}

void print( Node* root ){
    cout << root->Pos << ":" << root->Depth << ":" << root->Max << endl;
    for( int i = 0; i < root->Children.size(); i++ )
        print( root->Children[i] );
}

pair<int, int> DFS( Node* root, int &max_depth, int &max_pos, const int max_first ){
    for( int i = 0; i < root->Children.size(); i++ ){
        if( root->Children[i]->Pos == max_first )
            continue;
        DFS( root->Children[i], max_depth, max_pos, max_first );
    }
    if( root->Depth > max_depth ){
        max_depth = root->Depth;
        max_pos = root->Pos;
    }
    pair<int, int> k = { max_depth, max_pos };
    return k;
}

void MaxDepthV2( Node* root, const int maxF, const int maxS ){
    if( root->Max == 0 )
        root->Max = max( root->Depth + maxS, max( root->Parent->Max + 1, maxF - root->Depth ) );
    for( int i = 0; i < root->Children.size(); i++ )
        MaxDepthV2( root->Children[i], maxF, maxS );
}

void result( Node* root, map<int, int> &k ){
    k[root->Pos] = root->Max;
    for( int i = 0; i < root->Children.size(); i++ )
        result( root->Children[i], k );
}

int main() {
    int n, a, b, r = 0, z = 0;
    cin >> n;
    if( n == 1 ){
        cout << 0;
        return 0;
    }
    Node* root = new Node( 0, 0 );
    for( int i = 0; i < n - 1; i++ ){
        cin >> a >> b;
        Add( root, a, b );
    };
    pair<int, int> First = DFS( root, r, z );
    r = 0;
    z = 0;
    int k = 0;
    max_parent( root, First.second, k );
    pair<int, int> Second = DFS( root, r, z, k );
    MaxDepthV1( root, First.first, k );
    for( int i = 0; i < root->Children.size(); i++ )
        if( root->Children[i]->Pos == k )
            root = root->Children[i];
    int d = 0;
    maxTree( root, First.second, d, First.first, Second.first );
    root = root->Parent;
    MaxDepthV2( root, First.first, Second.first );
    map<int, int> res;
    result( root, res );
    for( int i = 0; i < n; i++ )
        cout << res[i] << endl;
	return 0;
}
