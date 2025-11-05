#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct BiTNode {
	char data;
	int lchild = -1, rchild = -1;
};

int n1, n2;

//创建二叉树并且返回根节点索引
int CreateBiTree(vector<BiTNode>& tree, int n)
{
	vector<bool> hasparent(n, false);
	for (int i = 0; i < n; i++) {
		char data;
		string leftidx, rightidx;
		cin >> data >> leftidx >> rightidx;
		tree[i].data = data;
		if (leftidx != "-") {
			tree[i].lchild = stoi(leftidx);
			hasparent[tree[i].lchild] = true;
		}
		if (rightidx != "-") {
			tree[i].rchild = stoi(rightidx);
			hasparent[tree[i].rchild] = true;
		}
	}

	//找根节点
	for (int i = 0; i < n; i++)
		if (!hasparent[i])
			return i;
	return -1;
}

//判断两棵树是否同构
bool judge(vector<BiTNode>& tree1, int root1, vector<BiTNode>& tree2, int root2)
{
	//两棵空树
	if (root1 == -1 && root2 == -1) return true;
	//一棵空一棵不空
	if ((root1 == -1 && root2 != -1) || (root1 != -1 && root2 == -1)) return false;
	//根节点数据不同
	if (tree1[root1].data != tree2[root2].data) return false;

	//情况1：左对左，右对右
	bool case1 = judge(tree1, tree1[root1].lchild, tree2, tree2[root2].lchild)
		&& judge(tree1, tree1[root1].rchild, tree2, tree2[root2].rchild);
	//情况2：左对右，右对左
	bool case2 = judge(tree1, tree1[root1].lchild, tree2, tree2[root2].rchild)
		&& judge(tree1, tree1[root1].rchild, tree2, tree2[root2].lchild);

	return case1 || case2;
}

//求树的深度
int getdepth(vector<BiTNode>& tree, int root)
{
	if (root == -1) return 0;
	int leftdepth = getdepth(tree, tree[root].lchild);
	int rightdepth = getdepth(tree, tree[root].rchild);
	return max(leftdepth, rightdepth) + 1;
}

int main()
{
	cin >> n1;
	vector<BiTNode> tree1(n1);
	int root1 = -1;
	if(n1>0)
	    root1=CreateBiTree(tree1, n1);
	cin >> n2;
	vector<BiTNode> tree2(n2);
	int root2 = -1;
	if(n2>0)
	    root2 = CreateBiTree(tree2, n2);

	bool result = false;
	if (n1 == 0 && n2 == 0)
		result = true;
	else if (n1 == n2 && n1 > 0)
		result = judge(tree1, root1, tree2, root2);
	cout << (result ? "Yes" : "No") << endl;

	int depth1 = (n1 > 0) ? getdepth(tree1, root1) : 0;
	int depth2 = (n2 > 0) ? getdepth(tree2, root2) : 0;
	cout << depth1 << endl;
	cout << depth2 << endl;

	return 0;
}