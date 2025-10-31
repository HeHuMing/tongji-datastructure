#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<long long> M(100, 0);
    M[0] = 0;
    M[1] = 1;

    for (int i = 2; i < 100; i++) {
        M[i] = M[i - 1] + M[i - 2] + 1;
    }

    int n;
    while (cin >> n) {
        if (n == -1) break;

        long long males = M[n];
        long long females = (n == 0) ? 0 : M[n - 1];
        long long total = males + females + 1;

        cout << males << " " << total << endl;
    }

    return 0;
}