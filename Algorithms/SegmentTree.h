#pragma once

#include <stdexcept>
#include <vector>

namespace MintLib {
	template <class Type = int>
	class SegmentTree {
	private:
		// variables of Segment Tree
		std::size_t n = 0;
		std::vector<Type> tree;	 // where i store Segment Tree (i store indicies of elements)
		std::vector<Type> array; // init array;

		// base functions of Segment Tree
		//
		// Left == (node << 1) because we need to go to the next level of tree: next = parent * 2
		// Right == (node << 1) + 1, because -\\-: next = parent * 2 + 1;
		Type Left(Type node) {
			return (node << 1);
		}

		Type Right(Type node) {
			return (node << 1) + 1;
		}

		void Build(Type parent, Type left, Type right) {
			if (left == right) {
				tree[parent] = left;
			} else {
				Type mid = (left + right) / 2;
				Build(SegmentTree::Left(parent), left, mid);
				Build(SegmentTree::Right(parent), mid + 1, right);
				
				Type node_left = tree[SegmentTree::Left(parent)];
				Type node_right = tree[SegmentTree::Right(parent)];
				tree[parent] = (array[node_left] <= array[node_right] ? node_left : node_right);
			}
		}	

		Type rmq(Type parent, Type left, Type right, Type i, Type j) {
			if (left > j || right < i) {
				return -1;
			}
			if (left >= i && right <= j) {
				return tree[parent];
			}

			Type mid = (left + right) / 2;
			Type child1 = rmq(SegmentTree::Left(parent), left, mid, i, j);
			Type child2 = rmq(SegmentTree::Right(parent), mid + 1, right, i, j);

			if (child1 == -1) {
				return child2;
			}
			if (child2 == -1) {
				return child1;
			}

			return (array[child1] <= array[child2] ? child1 : child2);
		}

	public:
		
		SegmentTree(std::vector<Type> init_arr) : n(init_arr.size()), array(std::move(init_arr)) {
			tree.resize(4 * n);
			SegmentTree::Build(1, 0, n - 1);
		} 
		
		Type rmq(Type i, Type j) {
			if ((i < 0 && j < 0) || (i >= n && j >= n)) {
				throw std::runtime_error("Out of bounds");	
			} else if (i > j) {
				throw std::runtime_error("i > j == wrong interval");
			}

			return rmq(1, 0, n - 1, i, j);
		}
	};
}

namespace mtl = MintLib;
