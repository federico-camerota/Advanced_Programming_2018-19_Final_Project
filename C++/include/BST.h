//: include/BST.h

#ifndef __BST_H__
#define __BST_H__

#include <functional>
#include <utility>
#include <memory>


template <class K, class V, class Comp = std::less<K>>
class BST{

    public:
	//!Alias for the type of keys in the tree
	using key_type = K;
	//!Alias for the type of values associated to keys in the tree
	using value_type = V;
	//!Alias for the key-value pair. The key is declared as const to prevent it from being changed once in the tree.
	using pair_type = std::pair< const K, V>;

    private:

	struct BST_node;
	class BST_iterator;
	class BST_const_iterator;

	using node_type = BST_node;

	std::unique_ptr<node_type> root;
	static node_type nullnode;

	/**
	 * Utility function to insert in the BST a full subtree. Elements of the subtree are
	 * inserted in the BST starting at the root and then recursively inserting the
	 * left and right subtrees.
	 * @param subtree subtree to copy into the BST
	 */
	void insert( const node_type& subtree);
    public:

	/** 
	 * Create an empty BST
	 */
	BST () 
	    : root{new node_type{}}
	{}

	/**
	 * Copy constructor, create a new BST having the same key-value pairs as other
	 * @param other BST to copy from
	 */
	BST (const BST<K,V,Comp> &other) 
	    : BST()
	{
	    insert(*other.root);//recursively inserts all nodes in other starting at the root node
	}
	/**
	 * Move constructor, create a new BST by swapping members.
	 * @param other BST to move
	 */
	BST (BST<K,V,Comp> &&other) {

	    root.swap(other.root);
	}
	/**
	 * Default destructor
	 */
	~BST() = default;

	
	using iterator = BST_iterator;
	using const_iterator = BST_const_iterator;

        node_type* get_min() const;

        iterator find(key_type key, node_type* node) const;

        iterator begin() {return iterator{get_min()};}
        iterator end() {return iterator{&nullnode};}

        const_iterator begin() const {return const_iterator{get_min()};}
        const_iterator end() const {return const_iterator{&nullnode};}

        const_iterator cbegin() const {return const_iterator{get_min()};}
        const_iterator cend() const {return const_iterator{&nullnode};}

	/**
	 * Insert a key-value pair in the BST.
	 * @param pair the key-value pair to insert
	 */
	void insert(const pair_type& pair){

	    insert(pair.first, pair.second);
	}
	/**
	 * Insert a key-value pair in the BST formed by the given key and value.
	 * @param key the key in the pair
	 * @param value the value in the pair
	 */
	void insert(const key_type& key, const value_type& value);

};


template<class K, class V, class Comp>
class BST<K,V,Comp>::BST_node {
	static Comp compare;
	std::unique_ptr<node_type> left_child, right_child;
	node_type* parent;
	pair_type data;

	BST_node() = default;
	BST_node(const key_type key, value_type value, node_type* father)
	 : left_child{nullptr}, right_child{nullptr}, parent{father}, data{key, value}
	{}
	std::unique_ptr<node_type>& get_left() {return left_child;}
	std::unique_ptr<node_type>& get_right() {return right_child;}
	pair_type& get_data() {return data;}
	/**
	 * Return a const reference to the key-value pair in the node.
	 * @return a const reference to the key-value pair in the node.
	 */
	const pair_type& get_data() const {return data;}
	node_type* get_parent() const {return parent;}
};

#endif
