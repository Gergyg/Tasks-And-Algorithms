#include <iostream>
#include "converter_of_number_systems.h"

int main() {

	while (true) {
		int base_first = 0, base_second = 0;
		std::string number{};

		std::cout << "Base first: ";
		std::cin >> base_first;
		std::cout << "Base second: ";
		std::cin >> base_second;

		std::cout << "Number: ";
		std::cin >> number;
		std::cout << MintLib::Convert::FromBaseToBase(base_first, base_second, number) << '\n';
	}

	return 0;
}
