/****************************************************************************
Дано число N &lt; 10^6 и последовательность пар целых чисел из [-2^31..2^31]
длиной N.

Построить декартово дерево из N узлов, характеризующихся парами чисел
{Xi, Yi}.

Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом
дереве.

Добавление узла в декартово дерево выполняйте второй версией алгоритма,
рассказанного на лекции:

- При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим
приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в
первом поддереве все ключи меньше x, а во втором больше или равны x.
Получившиеся два дерева сделайте дочерними для нового узла (x, y).
Новый узел вставьте на место узла P.

Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
****************************************************************************/

/****************************************************************************

Задача 2_2 Вычислить количество узлов в самом широком слое декартового дерева
и количество узлов в самом широком слое наивного дерева поиска. Вывести их
разницу. Разница может быть отрицательна.

  in    | out
  ----- | ---
  10    |
  5 11  |
  18 8  |
  25 7  |
  50 12 |
  30 30 |
  15 15 |
  20 10 |
  22 5  |
  40 20 |
  45 9  | 1

  in    | out
  ----- | ---
  10    |
  38 19 |
  37 5  |
  47 15 |
  35 0  |
  12 3  |
  0 42  |
  31 37 |
  21 45 |
  30 26 |
  41 6  | 1

****************************************************************************/



#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

using namespace std;
struct Node
{
   int Key;
   Node *left,*right;
};


void del(Node *&Tree){
   if (Tree!=NULL)
	{
	   del(Tree->left);
	   del(Tree->right);
	   delete Tree;
	   Tree = NULL;
	}

}

void add(int Key,Node *&MyTree)
{
	if (NULL==MyTree)
    {
		MyTree=new Node;
		MyTree->Key=Key;
		MyTree->left=MyTree->right=NULL;
	}
    if (Key<MyTree->Key)
    {
        if (MyTree->left!=NULL) add(Key,MyTree->left);
        else
        {
            MyTree->left=new Node;
            MyTree->left->left=MyTree->left->right=NULL;
            MyTree->left->Key=Key;
        }
    }
    if (Key>MyTree->Key)
    {
        if (MyTree->right!=NULL) add(Key,MyTree->right);
        else
        {
        MyTree->right=new Node;
        MyTree->right->left=MyTree->right->right=NULL;
        MyTree->right->Key=Key;
        }
    }
}

struct Treep {
	int key, prior;
	Treep * l, * r;
	Treep() { }
	Treep (int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};
typedef Treep * TreepType;


void del1(Treep *&Tree){
   if (Tree!=NULL)
	{
	   del1(Tree->l);
	   del1(Tree->r);
	   delete Tree;
	   Tree = NULL;
	}

}

void split (TreepType t, int key, TreepType & l, TreepType & r) {
	if (!t)
		l = r = NULL;
	else if (key < t->key)
		split (t->l, key, l, t->l),  r = t;
	else
		split (t->r, key, t->r, r),  l = t;
}

void insert (TreepType & t, TreepType it) {
	if (!t)
		t = it;
	else if (it->prior > t->prior)
		split (t, it->key, it->l, it->r),  t = it;
	else
		insert (it->key < t->key ? t->l : t->r, it);
}

void merge (TreepType & t, TreepType l, TreepType r) {
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r),  t = l;
	else
		merge (r->l, l, r->l),  t = r;
}

void erase (TreepType & t, int key) {
	if (t->key == key)
		merge (t, t->l, t->r);
	else
		erase (key < t->key ? t->l : t->r, key);
}

TreepType unite (TreepType l, TreepType r) {
	if (!l || !r)  return l ? l : r;
	if (l->prior < r->prior)  swap (l, r);
	TreepType lt, rt;
	split (r, l->key, lt, rt);
	l->l = unite (l->l, lt);
	l->r = unite (l->r, rt);
	return l;
}


void postOrder(Node* root, int* p, int lvl) {
    if (root) {
        postOrder(root->left,p,lvl+1);
        postOrder(root->right,p,lvl+1);
        p[lvl]++;
    }
}

void postOrder2(Treep* root, int* p, int lvl) {
    if (root) {
        postOrder2(root->l,p,lvl+1);
        postOrder2(root->r,p,lvl+1);
        p[lvl]++;
    }
}

int main()
{
    int n,x,y, max1 = INT_MIN, max2 = INT_MIN;
    int* p = new int[1000000];
    int* l = new int[1000000];
    Node* Tree = NULL;
    Treep* Tree2 = NULL;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        cin >> x >> y ;
        add(x, Tree);
        Treep* k = new Treep;
        k->l = NULL;
        k->r = NULL;
        k->key = x;
        k->prior = y;
        insert(Tree2,k);
    };
    postOrder(Tree,p,0);
    postOrder2(Tree2,l,0);
    for(int i=0;i<n;i++)
    {
        if(p[i]>max1)
        {
            max1=p[i];
        };
        if(l[i]>max2)
        {
            max2=l[i];
        }

    };
    cout << max2-max1 << endl;
    del(Tree);
    del1(Tree2);
    return 0;
}
