//: include/BST.h

#ifndef __BST_H__
#define __BST_H__

#include <functional>
#include <utility>
#include <memory>


template <class K, class V, class Comp = std::less<K>>
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

        node_type* get_min() const;

        iterator find(key_type key, node_type* node) const;

        iterator begin() {return iterator{getMin()};}
        iterator end() {return iterator{nullptr};}

        const_iterator begin() const {return const_iterator{getMin()};}
        const_iterator end() const {return const_iterator{nullptr};}

        const_iterator cbegin() const {return const_iterator{getMin()};}
        const_iterator cend() const {return const_iterator{nullptr};}

};


template<class K, class V, class Comp>
class BST<K,V,Comp>::BST_node {
	static Comp compare;
	std::unique_ptr<node_type> left_child, right_child;
	node_type* parent;
	pair_type data;

       	public:
	    BST_node() = default;
 	    BST_node(const key_type key, value_type value, node_type* father)
	     : left_child{nullptr}, right_child{nullptr}, parent{father}, data{key, value}
	    {}
	    std::unique_ptr<node_type>& get_left() {return left_child;}
	    std::unique_ptr<node_type>& get_right() {return right_child;}
            pair_type& get_data() {return data;}
            node_type* get_parent() const {return parent;}
};

#endif
