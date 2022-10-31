#pragma once

#include <vector>

template <class Type = int>
class SegmentTree {
private:
	// variables of Segment Tree
	std::vector<Type> tree;	 // where i store Segment Tree (i store indicies of elements)
	std::vector<Type> array; // init array;
	std::size_t n = 0;

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

public:

};
