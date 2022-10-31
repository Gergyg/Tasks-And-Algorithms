#include <iostream>
#include <vector>
#include "SegmentTree.h"

int main() {
	srand(time(0));

	int n = rand() % 10 + 1;
	std::cout << n << '\n';
	// std::cin >> n;

	std::vector<int> a(n); 
	for (int i = 0; i < n; ++i) {
		a[i] = rand() % 20 + 1;
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';

	mtl::SegmentTree<int> segTree(a);
	int i = rand() % n, j = rand() % (n - i) + i;

	// i = -1; j = n + 1;
	std::cout << i + 1 << ' ' << j + 1 << '\n';
//	std::cin >> i >> j;

	
	std::cout << a[segTree.rmq(i, j)] << '\n';	


	return 0;
}
