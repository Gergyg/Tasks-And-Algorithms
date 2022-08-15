#pragma once
#include <iostream>
#include <algorithm>

namespace MintLib {
	class Convert {	// converter of number_systems
	// if number_system more_than ([0;9] + [A;Z]) => UB
	public:
		template <class Base>
		static size_t FromBaseToDecimal(const Base& base, std::string& number) {
			size_t decimal = 0;
			size_t power = 1;
			for (int i = (int)number.size() - 1; i >= 0; --i) {
			 	int digit = (number[i] >= 'A' ? 10 + number[i] - 'A' : number[i] - '0');	
				decimal += power * digit;
				power *= base;
			}
			return decimal;
		}

		template <class Base, class Type>
		static std::string FromDecimalToBase(const Base& base, Type number) {
			std::string result_number{};

			while (number) {
				size_t remainder = number % base;
				char digit = (remainder >= 10 ? 'A' + remainder - 10 : remainder + '0');	
				result_number += digit;
				number /= base;
			}
			
			std::reverse(result_number.begin(), result_number.end());
			return result_number;
		}

		template <class Base>
		static std::string FromBaseToBase(const Base& from, const Base& to, std::string& number) {
			auto decimal_representation = FromBaseToDecimal(from, number); 
			auto base_to_representation = FromDecimalToBase(to, decimal_representation);
			return base_to_representation;
		}
	};
}

