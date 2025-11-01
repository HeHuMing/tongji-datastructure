#include <iostream>
#include <string>
using namespace std;

class Queue {
private:
    int* data;          // 存储队列元素
    int* maxQueue;      // 辅助队列，存储可能成为最大值的元素索引
    int front, rear;    // 主队列的头尾指针
    int maxFront, maxRear; // 辅助队列的头尾指针
    int capacity;       // 队列容量
    int size;           // 当前队列大小

public:
    Queue(int n) {
        capacity = n + 1; // 多一个位置用于区分空和满
        data = new int[capacity];
        maxQueue = new int[capacity];
        front = rear = 0;
        maxFront = maxRear = 0;
        size = 0;
    }

    ~Queue() {
        delete[] data;
        delete[] maxQueue;
    }

    bool isFull() {
        return size == capacity - 1;
    }

    bool isEmpty() {
        return size == 0;
    }

    bool enqueue(int v) {
        if (isFull()) {
            return false;
        }

        // 入队主队列
        data[rear] = v;
        rear = (rear + 1) % capacity;
        size++;

        // 维护最大值队列：从尾部移除所有比当前元素小的元素
        while (maxFront != maxRear && data[maxQueue[(maxRear - 1 + capacity) % capacity]] < v) {
            maxRear = (maxRear - 1 + capacity) % capacity;
        }
        maxQueue[maxRear] = (rear - 1 + capacity) % capacity;
        maxRear = (maxRear + 1) % capacity;

        return true;
    }

    int dequeue() {
        if (isEmpty()) {
            return -1;
        }

        int result = data[front];

        // 如果出队的元素是当前最大值，也从最大值队列中移除
        if (front == maxQueue[maxFront]) {
            maxFront = (maxFront + 1) % capacity;
        }

        front = (front + 1) % capacity;
        size--;

        return result;
    }

    int getMax() {
        if (isEmpty()) {
            return -1;
        }
        return data[maxQueue[maxFront]];
    }

    void printAll() {
        if (isEmpty()) {
            return;
        }

        int i = front;
        bool first = true;
        while (i != rear) {
            if (!first) {
                cout << " ";
            }
            cout << data[i];
            i = (i + 1) % capacity;
            first = false;
        }
        cout << endl;
    }
};

int main() {
    int n;
    cin >> n;

    Queue queue(n);
    string command;

    while (cin >> command) {
        if (command == "dequeue") {
            if (queue.isEmpty()) {
                cout << "Queue is Empty" << endl;
            }
            else {
                cout << queue.dequeue() << endl;
            }
        }
        else if (command == "enqueue") {
            int m;
            cin >> m;
            if (!queue.enqueue(m)) {
                cout << "Queue is Full" << endl;
            }
        }
        else if (command == "max") {
            if (queue.isEmpty()) {
                cout << "Queue is Empty" << endl;
            }
            else {
                cout << queue.getMax() << endl;
            }
        }
        else if (command == "quit") {
            queue.printAll();
            break;
        }
    }

    return 0;
}