#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

#define max_points 10000

//用于记录初始的有序树
typedef struct SqTNode {
	int data;
	int parent = -1;
	vector<int> child; //记录每个节点的所有孩子
}SqTNode;

//用于记录重构后的二叉树
typedef struct BiTNode {
	int data;
	int lchild = -1, rchild = -1;
}BiTNode;

int getDepth(vector<BiTNode>& newnode)
{
	if (newnode.empty()) return 0;

	vector<int> depth(newnode.size(), 0);
	int result = 0;

	for (int i = 0; i < newnode.size(); i++) {
		// 计算左孩子深度（深度+1）
		if (newnode[i].lchild != -1) {
			depth[newnode[i].lchild] = depth[i] + 1;
			result = max(result, depth[newnode[i].lchild]);
		}

		// 计算右孩子深度（深度+1）
		if (newnode[i].rchild != -1) {
			depth[newnode[i].rchild] = depth[i] + 1;
			result = max(result, depth[newnode[i].rchild]);
		}
	}

	return result;
}

int main()
{
	int idx = 0;
	while (++idx) {
		string str;
		cin >> str;
		if (str == "#")
			break;
		if (str == "")
			continue;

		int depth1 = 0, depth2 = 0;
		int sum1 = 0;

		//构造初始有序树，并求深度（前缀和）
		stack<int> stk;
		int current_node = 0; //记录路径上走过的每一个节点
		int current_index = 0; //记录当前入栈的节点编号
		SqTNode node[max_points];
		stk.push(current_index);
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == 'd') {
				sum1++;
				stk.push(++current_index);
				node[current_index].parent = current_node;
				node[current_node].child.push_back(current_index);
				current_node = current_index;
			}
			else if (str[i] == 'u') {
				sum1--;
				stk.pop();
				current_node = stk.top();
			}
			depth1 = max(depth1, sum1);
		}

		//重构二叉树
		vector<BiTNode> newnode(current_index + 1);
		for (int i = 0; i <= current_index; i++) {
			newnode[i].data = i;
			if (!node[i].child.empty()) {
				newnode[i].lchild = node[i].child[0];
				for (int j = 0; j < node[i].child.size() - 1; j++)
					newnode[node[i].child[j]].rchild = node[i].child[j + 1];
			}

		}
		depth2 = getDepth(newnode);
		cout << "Tree " << idx << ": " << depth1 << " => " << depth2 << endl;
	}
	return 0;
}
