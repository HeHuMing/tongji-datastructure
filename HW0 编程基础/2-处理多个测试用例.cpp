#include <iostream>
#include <string>
using namespace std;
int main()
{
	while (1) {
		string str;
		getline(cin, str);
		if (str == "#")
			break;
		size_t sum = 0;
		for (size_t i = 0; i < str.size(); i++) {
			char ch = str[i];
			if (ch >= 'A' && ch <= 'Z')
				sum += (ch - 'A' + 1) * (i + 1);
			else
				sum += 0;
		}
		cout << sum << endl;
	}
	return 0;
}