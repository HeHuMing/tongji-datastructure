#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int T;
	cin >> T;
	while (T--) {
		int Ni, Mi;
		cin >> Ni >> Mi;

		vector<int> parent(Ni + 1, 0); //记录每个点的父节点，下标为当前点，数值为父节点
		for (int i = 0; i < Ni - 1; i++) {
			int a, b;
			cin >> a >> b;
			parent[b] = a;
		}

		for (int k = 0; k < Mi; k++) {
			int qa, qb;
			cin >> qa >> qb;  //两个查询节点
			vector<int> qa_path, qb_path; //记录查询节点到根节点路径上经过的节点
			qa_path.push_back(qa);
			while (1) {
				int father = parent[qa];
				if (father == 0)
					break;
				else {
					qa = father;
					qa_path.push_back(father);
				}
			}
			qb_path.push_back(qb);
			while (1) {
				int father = parent[qb];
				if (father == 0)
					break;
				else {
					qb = father;
					qb_path.push_back(father);
				}
			}

			//比较找到两条路径中第一个相同的节点
			int flag = 0;
			int ans = 0;
			for (int i = 0; i < qa_path.size(); i++) {
				int cur = qa_path[i];
				for (int j = 0; j < qb_path.size(); j++) {
					if (qb_path[j] == cur) {
						ans = cur;
						flag = 1;
						break;
					}
				}
				if (flag)
					break;
			}
			cout << ans << endl;
		}
	}
	return 0;
}