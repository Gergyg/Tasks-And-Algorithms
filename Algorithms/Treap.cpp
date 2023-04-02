#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>

const long long& kInf = 1e9 + 666;
const long long& kMaxN = 1e5 + 10;

class Treap {
public:
    struct Node {
        int x = 0, y = 0;
        int subtree_count = 0;  
        Node* left = nullptr;
        Node* right = nullptr;

        Node() = default;

        Node(int& x_) : x(x_) {
            y = rand() % kMaxN + 3;
            subtree_count += 1;
        }
    };

    ~Treap() {
        while (root != nullptr) {
            Erase(root->x);
        }
    }

    int GetSize(Node* node) {
        return node == nullptr ? 0 : node->subtree_count;
    }

    void Insert(int x) {
        auto [L, oldR] = Split(root, x);
        auto [M, R] = Split(oldR, x + 1);
        M = new Node(x);
        root = Merge(L, Merge(M, R));
        total_count += 1;
    }

    void Erase(int x) {
        auto [L, oldR] = Split(root, x);
        auto [M, R] = Split(oldR, x + 1);
        delete M;
        M = nullptr;
        root = Merge(L, R);
        total_count -= 1;
    }

    int FindKthMax(int k) {
        std::function<int(Node*, int)> find = [&](Node* node, int k) {
            auto left_count = GetSize(node->left);
            if (left_count + 1 == k) {
                return node->x;
            }
            if (left_count < k) {
                return find(node->right, k - (left_count + 1));
            } else {
                return find(node->left, k);
            }
        };
        return find(root, total_count - k + 1);
    }

private:

    std::pair<Node*, Node*> Split(Node* node, long long x) {
        if (node == nullptr) {
            return {nullptr, nullptr};
        }

        if (node->x < x) {
            auto [l, r] = Split(node->right, x);
            node->right = l;
            node->subtree_count = GetSize(node->left) + GetSize(node->right) + 1;
            return {node, r};
        } else {
            auto [l, r] = Split(node->left, x);
            node->left = r;
            node->subtree_count = GetSize(node->left) + GetSize(node->right) + 1;
            return {l, node};
        }
    }

    Node* Merge(Node* subtree_l, Node* subtree_r) {
        if (subtree_l == nullptr) {
            return subtree_r;
        }
        if (subtree_r == nullptr) {
            return subtree_l;
        }

        if (subtree_l->y < subtree_r->y) {
            subtree_l->right = Merge(subtree_l->right, subtree_r);
            subtree_l->subtree_count = 1 + GetSize(subtree_l->left) + GetSize(subtree_l->right);
            return subtree_l;
        } else {
            subtree_r->left = Merge(subtree_l, subtree_r->left);
            subtree_r->subtree_count = 1 + GetSize(subtree_r->left) + GetSize(subtree_r->right);
            return subtree_r;
        }
    }

private:
    Node* root = nullptr;
    int total_count = 0;
};

int32_t main() {
    //freopen("_in", "r", stdin);

    srand(time(nullptr));

    int n = 0;
    std::cin >> n;

    Treap treap;

    while(n--) {
        std::string request;
        std::cin >> request;
        int k = 0;
        std::cin >> k;

        if (request == "+1" || request == "1") {
            treap.Insert(k);
        } else if (request == "0") {
            std::cout << treap.FindKthMax(k) << '\n';
        } else {
            treap.Erase(k);
        }
    }

    return 0;
}
// ??

