#include <iostream>
using namespace std;

int josephus(int n, int m) {
    int survivor = 0; // f(1, m) = 0
    for (int i = 2; i <= n; i++) {
        survivor = (survivor + m) % i;
    }
    return survivor;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        cout << josephus(n, m) << endl;
    }
    return 0;
}