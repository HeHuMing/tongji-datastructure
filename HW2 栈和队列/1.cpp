#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool simulate(const string& inSeq, const string& outSeq) {
    stack<char> st;
    int i = 0, j = 0;
    int n = inSeq.length();

    while (j < outSeq.length()) {
        // 如果栈顶等于当前要出站的元素，则出栈
        if (!st.empty() && st.top() == outSeq[j]) {
            st.pop();
            j++;
        }
        // 否则从入站序列中取一个入栈
        else if (i < n) {
            st.push(inSeq[i]);
            i++;
        }
        // 如果入站序列已用完且栈顶不匹配，则失败
        else {
            return false;
        }
    }
    return true;
}

int main() {
    string inSeq;
    cin >> inSeq;

    string outSeq;
    while (cin >> outSeq) {
        if (simulate(inSeq, outSeq)) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
    }

    return 0;
}