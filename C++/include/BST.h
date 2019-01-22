//: include/BST.h

#ifndef __BST_H__
#define __BST_H__

#include <functional>
#include <utility>
#include <memory>

template <class K, class V, class Comp = std::less>
class BST{

    public:
	using key_type = K;
	using value_type = V;
	//! The key is declared as const to prevent it from being changed once in the tree
	using pair_type = std::pair< const K, V>;

    private:

	class BST_node;
	class BST_iterator;
	class BST_const_iterator;

	using node_type = BST_node;

	std::unique_ptr<node_type> root;
	static node_type nullnode;
	
    public:

	using iterator = BST_iterator;
	using const_iterator = BST_const_iterator;

}

#endif
