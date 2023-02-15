#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

const long long& kInf = 1e9 + 666;

std::vector<int> GenerateVec(int n);
template <class T> void ShowVec(const T& vec);

int SortSegment(std::vector<int>& nuts, int left, int right, int need) { // [left, right]
    while (left < right) {
        while (nuts[left] < need) {
            left += 1;
        }
        while (need < nuts[right]) {
            right -= 1;
        }
        if (left <= right) {
            std::swap(nuts[left], nuts[right]);
        }
    }
    return left;
}

std::pair<int, int> FindBoarders(auto& nuts, auto& founded, int need, int n) {
    int left = 0, right = n - 1;
    if (founded.empty()) {
        return {left, right};
    }
    auto it_left = founded.begin(), it_right = founded.end();

    while (left < right && it_right != it_left) {
        int mid = (left + right) / 2;
        auto it = founded.upper_bound(mid - 1);
        if (it != it_right) {
            if (need < nuts[*it]) {
                it_right = it;
                right = *it - 1;
            } else {
                it_left = it;
                left = *it + 1;
            }
        } else {
            --it_right;
            if (nuts[*it_right] > need) {
                right = *it_right - 1;
            } else {
                left = *it_right + 1;
                it_left = it_right;
                ++it_right;
            }
        }
        auto x = it_right;
        if (x == it_left || --x == it_left) break;
    }

    return {left, right};
}

int32_t main() {
    srand(time(nullptr));
    int n = 0;
    std::cin >> n;
    auto b = GenerateVec(n);
    auto nuts = GenerateVec(n);

    std::cout << "___BEFORE___" << '\n';
    ShowVec(b);
    ShowVec(nuts);

    std::set<int> founded;

    std::map<int, std::vector<int>> map;
    for (int i = 0; i < n; ++i) {
        auto [left, right] = FindBoarders(nuts, founded, b[i], n);
        int pivot = SortSegment(nuts, left, right, b[i]);
        founded.insert(pivot);
        map[b[i]].push_back(nuts[pivot]);
    }

    std::cout << "\n___AFTER___" << '\n';
    ShowVec(b);
    ShowVec(nuts);

    for (auto& [x, vv] : map) {
        std::cout << "bolt: " << x << " | gaiki: ";
        ShowVec(vv);
    }

    return 0;
}

std::vector<int> GenerateVec(int n) {
    std::vector<int> a(n);
    std::set<int> used;
    for (auto& item : a) {
        int x = (rand() % n) + 1;
        while (used.contains(x)) {
            x = (rand() % n) + 1;
        }
        item = x;
        used.insert(x);
    }
    return a;
}

template <class T>
void ShowVec(const T& vec) {
    for (auto& item : vec) {
        std::cout << item << ' ';
    }
    std::cout << '\n';
}

// ??

