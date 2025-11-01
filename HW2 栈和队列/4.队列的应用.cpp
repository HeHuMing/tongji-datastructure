#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };

void bfs(vector<vector<char>>& graph, vector<vector<bool>>& visited, int startX, int startY)
{
    queue<pair<int, int>> q;
    q.push({ startX, startY });
    visited[startX][startY] = true;

    while (!q.empty()) {
        pair<int, int> current = q.front();
        int x = current.first;
        int y = current.second;
        q.pop();

        // 检查四个方向
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            // 检查边界
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (graph[nx][ny] == '1' && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    q.push({ nx, ny });
                }
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    vector<vector<char>> graph(n, vector<char>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> graph[i][j];

    vector<vector<bool>> visited(n, vector<bool>(m, false));
   //先遍历矩阵边缘的1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (graph[i][j] == '1' && !visited[i][j]&&(i==0||i==n-1||j==0||j==m-1)) {
                bfs(graph, visited, i, j);
            }
        }
    }
    //再求连通块
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (graph[i][j] == '1' && !visited[i][j]) {
                bfs(graph, visited, i, j);
                count++;
            }
        }
    }

    cout << count << endl;
    return 0;
}