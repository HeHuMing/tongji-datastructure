#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, start;


void bfs(vector<vector<int>>& graph,int start)
{
	vector<bool> visited(n, false);
	vector<int> distance(n, 0);
	queue<int> q;
	visited[start] = true;
	distance[start] = 0;
	q.push(start);

	int max_time = 0;

	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int neighbor : graph[current]) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				distance[neighbor] = distance[current] + 1;
				max_time = max(max_time, distance[neighbor]);
				q.push(neighbor);
			}
		}
	}

	cout << max_time << endl;
}

int main()
{
	cin >> n >> start;
	vector<vector<int>> graph(n);
	for (int i = 0; i < n; i++) {
		int lchild, rchild;
		cin >> lchild >> rchild;
		if (lchild != -1){
			graph[i].push_back(lchild);
			graph[lchild].push_back(i);
		}
		if (rchild != -1) {
			graph[i].push_back(rchild);
			graph[rchild].push_back(i);
		}
	}

	bfs(graph, start);
	return 0;
}