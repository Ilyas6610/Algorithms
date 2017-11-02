/****************************************************************************
Дано число N &lt; 10^6 и последовательность целых чисел из [-2^31..2^31]
длиной N. Требуется построить бинарное дерево, заданное наивным порядком
вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если
root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое
поддерево root.
****************************************************************************/

/****************************************************************************

Задача 1_3 Выведите элементы в порядке post-order (снизу вверх).

  in    | out
  ----- | ---
  3     |
  2 1 3 | 1 3 2

  in    | out
  ----- | ---
  3     |
  1 2 3 | 3 2 1

  in    | out
  ----- | ---
  3     |
  3 1 2 | 2 1 3

****************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stack>

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

void PostOrder(Node *root)
{
    if (root == NULL)
    {
       return;
    };
    stack<Node *> s;
    stack<int> d;
    s.push(root);
    while (s.empty() == false)
    {
        Node *temp = s.top();
        s.pop();
        d.push(temp->Key);
        if (temp->left)
            s.push(temp->left);
        if (temp->right)
            s.push(temp->right);
    };
    while(d.empty() == false)
    {
        cout << d.top() << ' ';
        d.pop();
    }
    
}

int main()
{
    int n,x;
    cin >> n;
    Node* Tree = NULL;
    for(int i=0;i<n;i++)
    {
        cin >> x;
        add(x,Tree);
    };
    PostOrder(Tree);
    del(Tree);
    return 0;
}


