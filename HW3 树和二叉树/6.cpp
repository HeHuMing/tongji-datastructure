#include <iostream>
#include <string>
using namespace std;

typedef struct BiTNode {
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

BiTree createBiTree(string preorder, string inorder, bool& success)
{
	if (preorder.empty() || inorder.empty()) {
		if (preorder.empty() && inorder.empty()) {
			return NULL;
		}
		success = false;
		return NULL;
	}

	BiTree root = new BiTNode;
	root->data = preorder[0];
	root->lchild = NULL;
	root->rchild = NULL;

	//在中序中找到根节点的位置
	auto it = inorder.find(root->data);
	if (it == string::npos) {
		success = false;
		delete root;
		return nullptr;
	}

	//左子树的中序和前序
	string left_inorder = inorder.substr(0, it);
	string left_preorder = preorder.substr(1, left_inorder.size());

	//右子树的中序和前序
	string right_inorder = inorder.substr(it + 1);
	string right_preorder = preorder.substr(left_inorder.size() + 1);

	//递归构建左子树、右子树
	root->lchild = createBiTree(left_preorder, left_inorder, success);
	if (!success) {
		delete root;
		return NULL;
	}

	root->rchild = createBiTree(right_preorder, right_inorder, success);
	if (!success) {
		if (root->lchild) 
			delete root->lchild;
		delete root;
		return nullptr;
	}

	return root;
}

bool postorder(BiTree T)
{
	if (T) {
		if (postorder(T->lchild))
			if (postorder(T->rchild)) {
				cout << T->data;
				return true;
			}
		return false;
	}
	else
		return true;
}

// 释放二叉树内存
void deleteTree(BiTree root) {
	if (root) {
		deleteTree(root->lchild);
		deleteTree(root->rchild);
		delete root;
	}
}

int main()
{
	string str;
	while (getline(cin, str)) {
		if (str.empty()) continue;
		auto it = str.find(' ');
		string preorder = str.substr(0, it);
		string inorder = str.substr(it + 1);

		if (preorder.size() != inorder.size()) {
			cout << "Error" << endl;
			return 0;
		}

		bool success = true;
		BiTree root = createBiTree(preorder, inorder, success);
		if (success) {
			postorder(root);
			cout << endl;
			deleteTree(root);
		}
		else {
			cout << "Error" << endl;
		}
	}
	return 0;
}