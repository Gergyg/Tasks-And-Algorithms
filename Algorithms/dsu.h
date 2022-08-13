#pragma once

#include <iostream>
#include <vector>

namespace MintLib {
	template <class Type>
	class DSU {
	public:
		DSU() = default;
	
		DSU(const Type& n) {
			parent.resize(n);
			size.resize(n);
		}
		
		void MakeSet(const Type& vertex) {
			parent[vertex] = vertex;
			size[vertex] = 1;
		}

		void FindSet(const Type& vertex) { // return root of the set, where vertex located;
			if (vertex == parent[vertex]) {
				return vertex;
			}
			return parent[vertex] = FindSet(parent[vertex]);
		}

		void JoinSets(const Type& lhs, const Type& rhs) { // groups 2 sets into one: prent of root rhs - lhs
			lhs = FindSet(lhs);
			rhs = FindSet(rhs);
			if (lhs != rhs) {
				if (size[lhs] < size[rhs]) {
					std::swap(lhs, rhs);
				}
				parent[rhs] = lhs; 
				size[lhs] += size[rhs];
			}
		}

	private:
		std::vector<Type> parent{};
		std::vector<size_t> size{};
	};
};

