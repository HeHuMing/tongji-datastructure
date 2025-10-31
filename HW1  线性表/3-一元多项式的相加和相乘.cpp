#include <iostream>
using namespace std;

//多项式节点结构体
struct PolyNode {
	int coef;
	int exp;
	PolyNode* next;
	PolyNode(int c = 0, int e = 0) :coef(c), exp(e), next(NULL) {};
};

//多项式类
class Polynomial {
private:
	PolyNode* head; //头指针

public:
	//构造函数
	Polynomial()
	{
		head = new PolyNode(); //头节点
	}

	//析构函数
	~Polynomial()
	{
		clear();
		delete head;
	}

	//清空多项式
	void clear()
	{
		PolyNode* curr = head->next;
		while (curr) {
			PolyNode* temp = curr;
			curr = curr->next;
			delete temp;
		}
		head->next = NULL;
	}

	//构建多项式
	void build(int* arr, int size)
	{
		//重置多项式
		clear();
		PolyNode* tail = head;

		for (int i = 0; i < size; i += 2) {
			int coef = arr[i];
			int exp = arr[i + 1];

			//创建新节点
			PolyNode* newNode = new PolyNode(coef, exp);
			tail->next = newNode; //带表头节点，head指针不动，尾插法
			tail = newNode;
		}
	}

	//添加项
	void add(int coef, int exp)
	{
		if (coef == 0)
			return;  //系数为0不添加

		PolyNode* prev = head;
		PolyNode* curr = head->next;

		//找到插入位置
		while (curr && curr->exp < exp) {
			prev = curr;
			curr = curr->next;
		}

		if (curr && curr->exp == exp) {  //指数相同，合并系数
			curr->coef += coef;
			if(curr->coef==0){   //系数为0，删除节点
				prev->next = curr->next;
				delete curr;
			}
		}
		else {   //插入新节点
			PolyNode* newNode = new PolyNode(coef, exp);
			newNode->next = curr;
			prev->next = newNode;
		}
	}

	//多项式加法
	Polynomial add(const Polynomial& other) const
	{
		Polynomial result;
		PolyNode* p1 = head->next;
		PolyNode* p2 = other.head->next;
		PolyNode* tail = result.head;

		while (p1 && p2) {
			if (p1->exp < p2->exp) {
				tail->next = new PolyNode(p1->coef, p1->exp);
				tail = tail->next;
				p1 = p1->next;
			}
			else if (p1->exp > p2->exp) {
				tail->next = new PolyNode(p2->coef, p2->exp);
				tail = tail->next;
				p2 = p2->next;
			}
			else {  //p1->exp = p2->exp
				int sumcoef = p1->coef + p2->coef;
				if (sumcoef != 0) {
					tail->next = new PolyNode(sumcoef, p2->exp);
					tail = tail->next;
				}
				p1 = p1->next;
				p2 = p2->next;
			}
		}

		//处理剩余部分
		while (p1) {
			tail->next = new PolyNode(p1->coef, p1->exp);
			tail = tail->next;
			p1 = p1->next;
		}
		while (p2) {
			tail->next = new PolyNode(p2->coef, p2->exp);
			tail = tail->next;
			p2 = p2->next;
		}

		return result;
	}

	//多项式乘法
	Polynomial multiply(const Polynomial& other)const
	{
		Polynomial result;
		PolyNode* p1 = head->next;
		while (p1) {
			PolyNode* p2 = other.head->next;
			while (p2) {
				int coef = p1->coef * p2->coef;
				int exp = p1->exp + p2->exp;
				result.add(coef, exp);
				p2 = p2->next;
			}
			p1 = p1->next;
		}
		return result;
	}

	//输出多项式
	void print() const
	{
		PolyNode* curr = head->next;
		bool first = true;
		while (curr) {
			if (!first)
				cout << " ";
			cout << curr->coef << " " << curr->exp;
			first = false;
			curr = curr->next;
		}
		if (first == false)  //非空多项式
			cout << endl;
	}

	//判断是否为空多项式
	bool isempty() const
	{
		return head->next == NULL;
	}
};

int main()
{
	int m, n, op;
	cin >> m;
	int* arr1 = new int[2 * m];
	for (int i = 0; i < m * 2; i++)
		cin >> arr1[i];
	cin >> n;
	int* arr2 = new int[2 * n];
	for (int i = 0; i < 2 * n; i++)
		cin >> arr2[i];
	cin >> op;

	Polynomial poly1, poly2;
	poly1.build(arr1, 2 * m);
	poly2.build(arr2, 2 * n);

	if (op == 0) {
		Polynomial result = poly1.add(poly2);
		result.print();
	}
	else if (op == 1) {
		Polynomial result = poly1.multiply(poly2);
		result.print();
	}
	else {
		Polynomial result1 = poly1.add(poly2); 
		Polynomial result2 = poly1.multiply(poly2);
		result1.print();
		result2.print();
	}
	delete[] arr1;
	delete[] arr2;
	return 0;
}
