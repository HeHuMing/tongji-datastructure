#include <iostream>
#include <string>
#include <stack>
using namespace std;

typedef struct BiTNode {
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

int n;

bool print(char e)
{
	cout << e;
	return true;
}

typedef bool (*visitfuc)(char);
bool postorder(BiTree T,visitfuc visit)
{
	if (T) {
		if (postorder(T->lchild, visit))
			if (postorder(T->rchild, visit))
				if (visit(T->data))
					return true;
		return false;
	}
	else
		return true;
}
/*
6
push a
push b
push c
pop
pop
push d
pop
pop
push e
push f
pop
pop
*/

void CreateBiTree()
{
	stack<BiTree> stk;
	BiTree root = NULL;
	BiTree lastpop = NULL;
	bool start = true;

	for (int i = 0; i < 2 * n; i++) {
		string str;
		cin >> str;

		if (str == "push") {
			char val;
			cin >> val;
			BiTree newnode = new BiTNode;
			newnode->data = val;
			newnode->lchild = NULL;
			newnode->rchild = NULL;

			if (start) { //根节点
				root = newnode;
				start = false;
			}
			else {
				if (lastpop) {  //如果上一个命令是pop，则这个节点是pop出来的节点的右孩子
					lastpop->rchild = newnode;
					lastpop = NULL;
				}
				else  //如果上个命令是push，则这个节点是push节点的左孩子
					stk.top()->lchild = newnode;
			}
			stk.push(newnode);
		} //end of if push
		else if (str == "pop") {
			lastpop = stk.top();
			stk.pop();
		} //end of if pop
	}
	//cout << root->data << " " << lastpop->data << endl;
	//后序遍历
	postorder(root, print);
}

int main()
{
	cin >> n;
	CreateBiTree();
	return 0;
}