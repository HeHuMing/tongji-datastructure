#include <iostream>
#include <string>
using namespace std;

//定义学生信息结构体
struct student {
	string no;
	string name;
};

//顺序表类的实现
class SeqList {
private:
	student* data; //存储学生数据的数组
	int capacity;  //顺序表的容量
	int length;    //当前元素的个数

public:
	//构造函数
	SeqList(int n)
	{
		capacity = n + 10;
		data = new student[capacity];
		length = 0;
	}

	//析构函数
	~SeqList()
	{
		delete[] data;
	}

	//在末尾添加学生
	void addStudent(const string& no, const string& name)
	{
		if (length < capacity) {
			data[length].no = no;
			data[length].name = name;
			length++;
		}
	}

	//在第i个位置插入学生（位置从1开始）
	int insert(int i, const string& no, const string& name)
	{
		//位置不合法
		if (i<1 || i>length + 1)
			return -1;
		//表已满
		if (length >= capacity)
			return -1;

		//将i-1位置及之后的元素后移
		for (int j = length; j >= i; j--)
			data[j] = data[j - 1];
        //插入新元素
		data[i - 1].no = no;
		data[i - 1].name = name;
		length++;
		return 0;
	}

	//删除第i个位置的学生
	int remove(int i)
	{
		if (i<1 || i>length)
			return -1;

		//将i位置之后的学生前移
		for (int j = i - 1; j < length - 1; j++)
			data[j] = data[j + 1];

		length--;
		return 0;
	}

	//根据姓名查找
	int findByName(const string& name, student& result)
	{
		for (int i = 0; i < length; i++) {
			if (data[i].name == name) {
				result = data[i]; //学生信息赋给result
				return i + 1; //返回位置
			}
		}
		return -1; //没找到
	}

	//根据学号查找
	int findByNo(const string& no, student& result)
	{
		for (int i = 0; i < length; i++) {
			if (data[i].no == no) {
				result = data[i]; //学生信息赋给result
				return i + 1; //返回位置
			}
		}
		return -1;
	}

	//获取学生总数
	int getLength()
	{
		return length;
	}
};

int main()
{
	int n;
	cin >> n;

	//创建顺序表
	SeqList list(n);

	//输入学生信息
	for (int i = 0; i < n; i++) {
		string no, name;
		cin >> no >> name;
		list.addStudent(no, name);
	}

	string operation;
	while (cin >> operation) {
		if (operation == "insert") {
			int pos;
			cin >> pos;
			string no, name;
			cin >> no >> name;
			int result = list.insert(pos, no, name);
			cout << result << endl;
		}
		else if (operation == "remove") {
			int pos;
			cin >> pos;
			int result = list.remove(pos);
			cout << result << endl;
		}
		else if (operation == "check") {
			string way;
			cin >> way;
			if (way == "name") {
				string name;
				cin >> name;
				student result;
				int pos = list.findByName(name, result);
				if (pos != -1)
					cout << pos << " " << result.no << " " << result.name << endl;
				else
					cout << -1 << endl;
			}
			else if (way == "no") {
				string no;
				cin >> no;
				student result;
				int pos = list.findByNo(no, result);
				if (pos != -1)
					cout << pos << " " << result.no << " " << result.name << endl;
				else
					cout << -1 << endl;
			}
		}
		else if (operation == "end") {
			cout << list.getLength() << endl;
			break;
		}
	}
	return 0;
}