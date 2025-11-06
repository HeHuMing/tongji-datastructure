#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

// 树节点结构
struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char x) : val(x), left(nullptr), right(nullptr) {}
};

// 运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 中缀转后缀
string infixToPostfix(const string& infix) {
    stack<char> st;
    string postfix;

    for (char c : infix) {
        if (isalpha(c)) {
            // 操作数直接输出
            postfix += c;
        }
        else if (c == '(') {
            // 左括号入栈
            st.push(c);
        }
        else if (c == ')') {
            // 右括号：弹出直到遇到左括号
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // 弹出左括号
        }
        else {
            // 运算符：弹出优先级更高或相等的运算符
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // 弹出栈中剩余运算符
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

// 从后缀表达式构建表达式树
TreeNode* buildTree(const string& postfix) {
    stack<TreeNode*> st;

    for (char c : postfix) {
        if (isalpha(c)) {
            // 操作数：创建叶子节点
            st.push(new TreeNode(c));
        }
        else {
            // 运算符：创建根节点，弹出两个操作数作为左右子树
            TreeNode* node = new TreeNode(c);
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
            st.push(node);
        }
    }
    return st.top();
}

// 获取树的高度
int getHeight(TreeNode* root) {
    if (!root) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

// 计算表达式值
int evaluate(TreeNode* root, const map<char, int>& values) {
    if (!root) return 0;

    if (isalpha(root->val)) {
        // 叶子节点：返回变量值
        return values.at(root->val);
    }

    // 内部节点：递归计算左右子树
    int leftVal = evaluate(root->left, values);
    int rightVal = evaluate(root->right, values);

    switch (root->val) {
    case '+': return leftVal + rightVal;
    case '-': return leftVal - rightVal;
    case '*': return leftVal * rightVal;
    case '/': return leftVal / rightVal;
    }
    return 0;
}

// 输出表达式树
void printTree(TreeNode* root) {
    if (!root) return;

    int height = getHeight(root);
    int width = (1 << height) - 1; // 2^height - 1
    vector<vector<char>> canvas(2 * height - 1, vector<char>(width, ' '));

    // 使用DFS布局树
    struct NodeInfo {
        TreeNode* node;
        int row, col;
    };

    stack<NodeInfo> st;
    st.push({ root, 0, width / 2 });

    while (!st.empty()) {
        NodeInfo current = st.top();
        st.pop();

        TreeNode* node = current.node;
        int row = current.row;
        int col = current.col;

        // 放置当前节点
        canvas[row][col] = node->val;

        // 计算子节点的位置
        if (node->left || node->right) {
            int levelGap = (1 << (height - row / 2 - 2));

            if (node->left) {
                int leftRow = row + 2;
                int leftCol = col - levelGap;
                canvas[row + 1][col - 1] = '/';
                st.push({ node->left, leftRow, leftCol });
            }

            if (node->right) {
                int rightRow = row + 2;
                int rightCol = col + levelGap;
                canvas[row + 1][col + 1] = '\\';
                st.push({ node->right, rightRow, rightCol });
            }
        }
    }

    // 输出画布，去除行末空格
    for (int i = 0; i < canvas.size(); i++) {
        string line;
        for (int j = canvas[i].size() - 1; j >= 0; j--) {
            if (canvas[i][j] != ' ') {
                line = string(canvas[i].begin(), canvas[i].begin() + j + 1);
                break;
            }
        }
        cout << line << endl;
    }
}

int main() {
    string infix;
    int n;

    // 读取输入
    cin >> infix;
    cin >> n;

    map<char, int> values;
    for (int i = 0; i < n; i++) {
        char c;
        int x;
        cin >> c >> x;
        values[c] = x;
    }

    // 1. 转换为逆波兰式并输出
    string postfix = infixToPostfix(infix);
    cout << postfix << endl;

    // 2. 构建表达式树并输出
    TreeNode* root = buildTree(postfix);
    printTree(root);

    // 3. 计算表达式值并输出
    int result = evaluate(root, values);
    cout << result << endl;

    return 0;
}