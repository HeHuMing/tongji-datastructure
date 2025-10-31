#include <iostream>
#include <string>
using namespace std;

// 牌的结构
struct Card {
    string suit;
    string rank;
};

// 链表节点
struct Node {
    Card card;
    Node* prev;
    Node* next;

    Node(string s, string r) {
        card.suit = s;
        card.rank = r;
        prev = nullptr;
        next = nullptr;
    }
};

class PokerDeck {
private:
    Node* head;
    Node* tail;
    int count;

    // 将牌面转换为数字用于排序
    int rankToValue(const string& rank) {
        if (rank == "A") return 1;
        if (rank == "J") return 11;
        if (rank == "Q") return 12;
        if (rank == "K") return 13;
        return stoi(rank);
    }

    // 从链表中移除节点（不删除内存）
    void removeNode(Node* node) {
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == head) head = node->next;
        if (node == tail) tail = node->prev;
        count--;
    }

    // 在头部插入节点
    void insertAtHead(Node* node) {
        node->prev = nullptr;
        node->next = head;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = node;
        count++;
    }

public:
    PokerDeck() : head(nullptr), tail(nullptr), count(0) {}

    // Append操作：在尾部添加牌
    void append(string suit, string rank) {
        Node* newNode = new Node(suit, rank);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else {
            head = tail = newNode;
        }
        count++;
    }

    // Extract操作：抽取某种花色的所有牌，排序后放到顶部
    void extract(string suit) {
        if (count == 0) return;

        // 第一步：收集所有匹配花色的牌
        Node* extractedHead = nullptr;
        Node* extractedTail = nullptr;
        int extractedCount = 0;

        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            if (curr->card.suit == suit) {
                // 从原链表中移除
                removeNode(curr);

                // 添加到提取链表
                curr->prev = extractedTail;
                curr->next = nullptr;
                if (extractedTail) {
                    extractedTail->next = curr;
                }
                else {
                    extractedHead = curr;
                }
                extractedTail = curr;
                extractedCount++;
            }
            curr = nextNode;
        }

        if (extractedCount == 0) return;

        // 第二步：对提取的牌进行排序（冒泡排序）
        if (extractedCount > 1) {
            bool swapped;
            do {
                swapped = false;
                Node* current = extractedHead;
                while (current && current->next) {
                    int val1 = rankToValue(current->card.rank);
                    int val2 = rankToValue(current->next->card.rank);
                    if (val1 > val2) {
                        // 交换节点数据
                        Card temp = current->card;
                        current->card = current->next->card;
                        current->next->card = temp;
                        swapped = true;
                    }
                    current = current->next;
                }
            } while (swapped);
        }

        // 第三步：将排序后的牌插入到原链表头部
        if (extractedHead) {
            extractedTail->next = head;
            if (head) head->prev = extractedTail;
            head = extractedHead;
            if (!tail) tail = extractedTail;
            count += extractedCount;
        }
    }

    // Revert操作：反转整个牌堆
    void revert() {
        if (count <= 1) return;

        Node* curr = head;
        Node* temp = nullptr;

        while (curr) {
            // 交换prev和next指针
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            // 移动到下一个节点（原来的next，现在的prev）
            curr = curr->prev;
        }

        // 交换head和tail
        temp = head;
        head = tail;
        tail = temp;
    }

    // Pop操作：弹出顶部牌
    void pop() {
        if (count == 0) {
            cout << "NULL" << endl;
            return;
        }

        Node* topNode = head;
        cout << topNode->card.suit << " " << topNode->card.rank << endl;

        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }

        delete topNode;
        count--;
    }

    // 打印所有牌（从顶到底）
    void printAll() {
        if (count == 0) {
            cout << "NULL" << endl;
            return;
        }

        Node* curr = head;
        while (curr) {
            cout << curr->card.suit << " " << curr->card.rank << endl;
            curr = curr->next;
        }
    }

    // 析构函数：释放内存
    ~PokerDeck() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

int main() {
    int n;
    cin >> n;
    cin.ignore(); // 忽略第一行的换行符

    PokerDeck deck;

    for (int i = 0; i < n; i++) {
        string command;
        getline(cin, command);

        if (command == "Pop") {
            deck.pop();
        }
        else if (command.find("Append") == 0) {
            // 解析"Append Suit Rank"
            size_t firstSpace = command.find(' ');
            size_t secondSpace = command.find(' ', firstSpace + 1);
            string suit = command.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string rank = command.substr(secondSpace + 1);
            deck.append(suit, rank);
        }
        else if (command.find("Extract") == 0) {
            // 解析"Extract Suit"
            size_t spacePos = command.find(' ');
            string suit = command.substr(spacePos + 1);
            deck.extract(suit);
        }
        else if (command == "Revert") {
            deck.revert();
        }
    }

    deck.printAll();

    return 0;
}