#include <iostream>
#include <vector>

const int kMax = 61, kMod = 998244353;
std::vector<long long> factorial(kMax, 1);
std::vector<long long> invfact(kMax, 1);


long long BinPow(long long a, long long x) {
    if (x == 0) {
        return 1;
    } else if (x & 1) {
        return (BinPow(a, x - 1) * a) % kMod ;
    } else {
        long long tmp = BinPow(a, x / 2);
        return (tmp * tmp) % kMod;
    }
}

void PreCompute() {
	for (int i = 1; i < kMax; ++i) {
		factorial[i] = (factorial[i - 1] * i) % kMod;
	}

    int n = kMax - 1;
    invfact[n] = BinPow(factorial[n], kMod - 2);

    for (int i = n; i > 0; --i) {
        invfact[i - 1] = invfact[i] * i % kMod;
    }
}

long long Comb(int n, int r) {
	auto invdenominator = (invfact[r] * invfact[n - r]) % kMod;
	return factorial[n] * invdenominator;
}

int main() {
    PreCompute();

    int num_tests = 1;
    std::cin >> num_tests;

    while (num_tests--) {
        int n = 0;
        std::cin >> n;

        long long Aleksei_Won = 0, Boris_Won = 0;
        long long draw = 1;

        // draw: BAABBAABBAA...
        int count_a = n / 2;
        int count_b = n / 2;
        Aleksei_Won += Comb(n - 1, count_a - 1);
        count_b -= 1;
        --n;
        int n_cp = n;
        for (int i = 0; i + 1 < n_cp; ++i) {
            Aleksei_Won %= kMod;
            Boris_Won %= kMod;
            if (i % 4 < 2) {
                Boris_Won += Comb(n - 1, count_b - 1);
                count_a -= 1;
            } else {
                Aleksei_Won += Comb(n - 1, count_a - 1);
                count_b -= 1;
            }
            n -= 1;
        }

        std::cout << Aleksei_Won << ' ' << Boris_Won << ' ' << draw << '\n';
    }

    return 0;
}
// ??
