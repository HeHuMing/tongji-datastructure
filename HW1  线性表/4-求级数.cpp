#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class BigInt {
private:
    vector<int> digits;

public:
    BigInt() {}

    BigInt(long long n) {
        if (n == 0) {
            digits.push_back(0);
        }
        else {
            while (n > 0) {
                digits.push_back(n % 10);
                n /= 10;
            }
        }
    }

    BigInt(const string& s) {
        for (int i = s.length() - 1; i >= 0; i--) {
            digits.push_back(s[i] - '0');
        }
        removeLeadingZeros();
    }

    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    BigInt operator+(const BigInt& other) const {
        BigInt result;
        int carry = 0;
        int maxSize = max(digits.size(), other.digits.size());

        for (int i = 0; i < maxSize || carry; i++) {
            int sum = carry;
            if (i < digits.size()) sum += digits[i];
            if (i < other.digits.size()) sum += other.digits[i];

            result.digits.push_back(sum % 10);
            carry = sum / 10;
        }

        return result;
    }

    BigInt operator*(const BigInt& other) const {
        BigInt result;
        result.digits.resize(digits.size() + other.digits.size(), 0);

        for (int i = 0; i < digits.size(); i++) {
            int carry = 0;
            for (int j = 0; j < other.digits.size() || carry; j++) {
                long long product = result.digits[i + j] +
                    (long long)digits[i] * (j < other.digits.size() ? other.digits[j] : 0) +
                    carry;
                result.digits[i + j] = product % 10;
                carry = product / 10;
            }
        }

        result.removeLeadingZeros();
        return result;
    }

    BigInt power(int exponent) const {
        if (exponent == 0) return BigInt(1);

        BigInt result(1);
        BigInt base = *this;

        while (exponent > 0) {
            if (exponent & 1) {
                result = result * base;
            }
            base = base * base;
            exponent >>= 1;
        }

        return result;
    }

    string toString() const {
        string result;
        for (int i = digits.size() - 1; i >= 0; i--) {
            result += char(digits[i] + '0');
        }
        return result;
    }
};

BigInt calculateSeries(int N, int A) {
    if (A == 0) return BigInt(0);  // 所有项都是0

    BigInt sum(0);
    BigInt base(A);

    for (int k = 1; k <= N; k++) {
        BigInt term = BigInt(k) * base.power(k);
        sum = sum + term;
    }

    return sum;
}

int main() {
    int N, A;
    while (cin >> N >> A) {
        BigInt result = calculateSeries(N, A);
        cout << result.toString() << endl;
    }
    return 0;
}