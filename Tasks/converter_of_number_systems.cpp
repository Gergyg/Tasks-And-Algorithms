#include <iostream>
#include <string>
#include "converter_of_number_systems.h"
#include <iomanip>

namespace mtl = MintLib;

int main() {
	std::cout << "Current base class: first = 10, second = 2\n";
	int maxN = 20;
	for (int i = 1; i < maxN; ++i) {
		int base_first = 10, base_second = 2;
		std::string number{};

/*		std::cout << "Base first: ";
		std::cin >> base_first;
		std::cout << "Base second: ";
		std::cin >> base_second;
		std::cin >> number;

*/
		number = std::to_string(i);
		auto result = mtl::Convert::FromBaseToBase(base_first, base_second, number);

		if (result.size() < 10) {
			size_t diff = 10 - result.size();
			std::string suplement(diff, '0');
			result = suplement + result;
		}

		std::cout << '#' << std::left << std::setw(3) << i << result << '\n';
	}

	return 0;
}
