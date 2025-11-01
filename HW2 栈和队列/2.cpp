#include <iostream>
#include <string>
using namespace std;

template<typename T, int SIZE = 200>
class Stack {
private:
    T data[SIZE];
    int topIndex;
public:
    Stack() : topIndex(-1) {}

    void push(const T& x) {
        if (topIndex + 1 >= SIZE) {
            throw "Stack overflow";
        }
        data[++topIndex] = x;
    }

    T pop() {
        if (isEmpty()) {
            throw "Stack underflow";
        }
        return data[topIndex--];
    }

    T peek() const {
        if (isEmpty()) {
            throw "Stack empty";
        }
        return data[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }
};

int priority(char op) {
    if (op == '!') return 3;
    if (op == '&') return 2;
    if (op == '|') return 1;
    return 0; //()优先级取0，遇到才弹出
}

void opt(char op, Stack<bool>& valStack) {
    if (op == '!') {
        bool a = valStack.pop();
        valStack.push(!a);
    }
    else if (op == '&') {
        bool b = valStack.pop();
        bool a = valStack.pop();
        valStack.push(a && b);
    }
    else if (op == '|') {
        bool b = valStack.pop();
        bool a = valStack.pop();
        valStack.push(a || b);
    }
}

string removespaces(const string& s) {
    string result;
    for (char c : s) {
        if (!isspace(c)) {
            result += c;
        }
    }
    return result;
}

bool evaluate(const string& expr) {
    string str = removespaces(expr);
    Stack<bool> val_stack;
    Stack<char> op_stack;

    int i = 0;
    int n = str.length();

    while (i < n) {
        if (str[i] == 'V') {
            val_stack.push(true);
            i++;
        }
        else if (str[i] == 'F') {
            val_stack.push(false);
            i++;
        }
        else if (str[i] == '(') {
            op_stack.push('(');
            i++;
        }
        else if (str[i] == ')') {
            while (!op_stack.isEmpty() && op_stack.peek() != '(') {
                opt(op_stack.pop(), val_stack);
            }
            op_stack.pop(); // 弹出 '('
            i++;
        }
        else { // 运算符 ! & |
            // 处理优先级高的运算符
            while (!op_stack.isEmpty() && priority(op_stack.peek()) >= priority(str[i])) {
                opt(op_stack.pop(), val_stack);
            }
            op_stack.push(str[i]);
            i++;
        }
    }

    // 处理剩余运算符
    while (!op_stack.isEmpty()) {
        opt(op_stack.pop(), val_stack);
    }

    return val_stack.pop();
}

int main() {
    string line;
    int index = 1;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        bool result = evaluate(line);
        cout << "Expression " << index << ": " << (result ? "V" : "F") << endl;
        index++;
    }

    return 0;
}