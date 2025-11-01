#include <iostream>
using namespace std;
const int MAXN = 100010;

class stack {
private:
	int data[MAXN];
	int top_index;
public:
	stack() :top_index(-1){}

	void push(int value)
	{
		data[++top_index] = value;
	}

	int pop()
	{
		if (isempty()) return -1;
		return data[top_index--];
	}

	int top()
	{
		if (isempty()) return -1;
		return data[top_index];
	}

	bool isempty() {
		return top_index == -1;
	}

	void clear()
	{
		top_index = -1;
	}
};

int main()
{
	char str[MAXN];
	cin.getline(str, MAXN);
	int n = strlen(str);
	if (n == 0) {
		cout << "0 0" << endl;
		return 0;
	}

	stack s;
	int maxlen = 0;
	int startpos = 0;
	s.push(-1);

	for (int i = 0; i < n; i++) {
		if (str[i] == '(')
			s.push(i);
		else {
			s.pop();
			if (s.isempty())
				// 如果栈为空，说明当前右括号没有匹配的左括号
				// 将当前位置作为新的基准
				s.push(i);
			else {
				// 栈不为空，说明找到了匹配的括号对
				// 计算当前有效子串长度
				int currentlen = i - s.top();
				if (currentlen > maxlen) {
					maxlen = currentlen;
					startpos = s.top() + 1;
				}
			}
		}
	}
	cout << maxlen << " " << startpos << endl;
	return 0;
}