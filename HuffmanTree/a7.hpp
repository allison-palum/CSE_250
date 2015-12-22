#ifndef A7_HPP
#define A7_HPP

#include "symbol.hpp"
#include <queue>
#include <iostream>

class CompareNodes {
public:
	bool operator()(const bnode<symbol>* b1, const bnode<symbol>* b2) {
		if (b1->value.count == b2->value.count) return (b2->value.value < b1->value.value);
		else return (b2->value.count < b1->value.count);
	}
};

// IMPLEMENT YOUR FUNCTION huffman_tree
template <typename Iter>
bnode<symbol>* huffman_tree(Iter first, Iter last) {
	std::priority_queue<bnode<symbol>*, std::vector<bnode<symbol>* >, CompareNodes> pq;
	for (; first != last; ++first) {
		symbol* symb = new symbol(first->value, first->count);
		bnode<symbol>* bn = new bnode<symbol>(*symb, 0, 0);
		pq.push(bn);
	}

	//while (!pq.empty()) {
	//	bnode<symbol>* tbn = pq.top();
	//	std::cout << tbn->value.value << "/" << tbn->value.count << " ";
	//	pq.pop();
	//}

	while (pq.size() > 1) {
		bnode<symbol>* b1 = pq.top();
		pq.pop();
		bnode<symbol>* b2 = pq.top();
		pq.pop();
		symbol* s = new symbol(0, b1->value.count + b2->value.count);
		bnode<symbol>* b3 = new bnode<symbol>(*s, b1, b2);
		delete s;
		pq.push(b3);
	}
	return pq.top();
}

// IMPLEMENT YOUR FUNCTION release_tree
void release_tree(bnode<symbol>* root) {
	if (root){
		release_tree(root->left);
		release_tree(root->right);
		delete root;
	}
}

#endif // A7_HPP