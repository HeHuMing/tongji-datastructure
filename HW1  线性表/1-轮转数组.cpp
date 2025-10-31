#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int n, k;
	cin >> n >> k;
	vector<int> vec(n), ans(n);
	for (int i = 0; i < n; i++) {
		cin >> vec[i];
		if (i + k <= n - 1)
			ans[i + k] = vec[i];
		else 
			ans[i + k - n] = vec[i];
	}
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
	cout << endl;
	return 0;
}