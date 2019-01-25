//: include/BST.h

#ifndef __BST_H__
#define __BST_H__


#include <functional>
#include <utility>
#include <memory>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <iterator>


#ifdef __BST_DEV__
/**
 * Namespace containing all the testing tools for BST and
 * related classes.
 */
namespace BST_testing {

    /**
     * The Tester class provides a suite of tests to be performed on the
     * BST and related classes to test their correctness
     */
    class Tester;
}
#endif


namespace {

    template <class K, class V>
    struct BST_node;
    template <class K, class V>
    class BST_iterator;
    template <class K, class V>
    class BST_const_iterator;
}

template <class K, class V, class Comp = std::less<K>>
class BST{

    public:
	//!Alias for the type of keys in the tree
	using key_type = K;
	//!Alias for the type of values associated to keys in the tree
	using value_type = V;
	//!Alias for the key-value pair. The key is declared as const to prevent it from being changed once in the tree.
	using pair_type = std::pair< const K, V>;

	#ifdef __BST_DEV__
	friend BST_testing::Tester;
	#endif

    private:

	//!private alias for node type
	using node_type = BST_node<K,V>;

	std::unique_ptr<node_type> root;
	Comp compare{};

	/**
	 * Utility function to insert in the BST a full subtree. Elements of the subtree are
	 * inserted in the BST starting at the root and then recursively inserting the
	 * left and right subtrees.
	 * @param subtree subtree to copy into the BST
	 */
	void insert( const node_type& subtree);
	/**
	 * Utility function to insert median element in a given tree from a vector of pairs
	 */
	void insert_median(std::vector<pair_type>& , const size_t, const size_t);

    public:

	/** 
	 * Create an empty BST
	 */
	BST () = default;

	/**
	 * Copy constructor, create a new BST having the same key-value pairs as other
	 * @param other BST to copy from
	 */
	BST (const BST<K,V,Comp> &other)
	{
	    insert(*other.root);//recursively inserts all nodes in other starting at the root node
	}
        /**
         * Copy assignment, copy all the members from one tree to this
         * @param other BST to copy
         */
        BST& operator=(const BST<K,V,Comp> &other) {
            clear();    //free any memory
            auto temp{other};    //call copy constructor
            (*this) = std::move(temp);    //call move assignment
            return *this;
        }
	/**
	 * Move constructor, create a new BST by swapping members.
	 * @param other BST to move
	 */
	BST (BST<K,V,Comp> &&other) noexcept {

	    root.swap(other.root);
	}
        /**
         * Move assignment, move the members of other onto this.
         * @param other BST to move
         */
        BST& operator=(BST<K,V,Comp> &&other) noexcept {
            root = std::move(other.root);
            return *this;
        }
	/**
	 * Default destructor
	 */
	~BST() noexcept = default;

	
	//!Alias for iterators

	using iterator = BST_iterator<K,V>;
	//!Alias for const iterators
	using const_iterator = BST_const_iterator<K,V>;

        /**
         * Return a pointer to the node having the smallest key.
         */
        node_type* get_min() const noexcept;

        /**
         * Returns an iterator to the node corresponding having a key equal to the input key, end()
         * if it is not found. Moves down the tree exploiting the ordering of the keys.
         * @param key the sought-after key
         */
        iterator find(key_type key) const noexcept;

        /**
         * non-const begin and end functions. Allow the BST to support range for-loops.
         * begin returns an iterator to the node having the smallest key, end returns an iterator
         * to the null node.
         */
        iterator begin() noexcept {return iterator{get_min()};}
        iterator end() noexcept {return iterator{nullptr};}

        /**
         * const begin and end functions. They both return a const_iterator, according to the above rules
         */
        const_iterator begin() const noexcept {return const_iterator{get_min()};}
        const_iterator end() const noexcept {return const_iterator{nullptr};}

        /**
         * cbegin and cend behave like const begin and const end, but can be useful to force an algorithm
         * of the STL to not modify input iterators.
         */
        const_iterator cbegin() const noexcept {return const_iterator{get_min()};}
        const_iterator cend() const noexcept {return const_iterator{nullptr};}

	/**
	 * Insert a key-value pair in the BST composed by the given key and value.
	 * @param key the key in the pair
	 * @param value the value in the pair
	 */
	void insert(const key_type& key, const value_type& value);
	/**
	 * Insert a key-value pair in the BST.
	 * @param pair the key-value pair to insert
	 */
	void insert(const pair_type& pair){

	    insert(pair.first, pair.second);
	}
	/**
	 * Balance the current BST.
	 */
	void balance();
	/**
	 * Remove all key-value pairs from the BST.
	 */
	void clear(){
	
	    root.reset(nullptr);
	}
	
	value_type& operator[] (const key_type&);
	const value_type& operator[] (key_type&&) const;

};

/**
 * Node struct
 */
namespace{
    template<class K, class V>
    struct BST_node {
	    
	    using pair_type=typename BST<K,V>::pair_type;
	    using key_type=typename BST<K,V>::key_type;
	    using value_type=typename BST<K,V>::value_type;
	    using node_type=BST_node<K,V>;

	    std::unique_ptr<node_type> left_child, right_child;
	    node_type* parent;
	    pair_type data;

	    BST_node() = delete;
	    BST_node(const key_type key, value_type value, node_type* father)
	     : left_child{nullptr}, right_child{nullptr}, parent{father}, data{key, value}
	    {}
	    ~BST_node() = default;
    };
}

/**
 * Iterator class, made compliant with the STL. In particular, the iterator allows to traverse the tree
 * in-order, that is from the smallest to the greatest key.
 */
namespace {
template<class K, class V>
class BST_iterator : public std::iterator<std::forward_iterator_tag, std::pair<const K,V>>{

        using pair_type = typename BST<K,V>::pair_type;
        using node_type=BST_node<K,V>;

        node_type* current;

    public:
        BST_iterator(node_type* n) : current{n} {}
        /**
         * dereferencing operator, returns an std::pair<const K, V> of the current node
         */
        pair_type& operator*() const {return current->data;}
        /**
         * pre-increment operator. Implements algorithm for retrieving
         * the successor of a node.
         */
        BST_iterator& operator++() {
            if (current->right_child != nullptr) {    //if current node has right child, go down right and then as much to the left as possible
                current = current->right_child.get();
                while (current->left_child.get()) {
                    current = current->left_child.get();
                }
                return *this;
            }
            else {     //otherwise, go up until you reach the root or you find a node that is not the right child of its parent
                node_type* p = current->parent;
                while (p != nullptr && current == p->right_child.get()) {
                    current = p;
                    p = p->parent;
                }
                current = p;
                return *this;
	    }    
        }

        bool operator==(const BST_iterator& other) {return current == other.current;} //tests whether two iterators share the same current node
        bool operator!=(const BST_iterator& other) {return !(*this==other);}
};
}

/**
const_iterator class. Populated with the functions of the iterator class, with the
exception of the dereferencing operator that is const, as appropriate
*/
namespace {
template<class K, class V>
class BST_const_iterator : public BST_iterator<K,V> {
    using base = ::BST_iterator<K,V>;
    using pair_type = typename BST<K,V>::pair_type;
    public:
	using base::BST_iterator;
	const pair_type& operator*() const {return base::operator*();}
	using base::operator++;
	using base::operator==;
	using base::operator!=;
};
}


#ifdef __BST_DEV__
namespace BST_testing{

    class Tester{
    
	public:

	    Tester() = default;

	    void test();
	    bool bst_default_ctor();
	    bool bst_insert();
	    bool bst_copy_ctor();
	    bool bst_deep_copy();
	    bool bst_move_ctor();
            bool test_move_copy_assignment();
	    bool bst_balance();
	    bool test_iterators();
	    bool test_find();
    };
}
#endif

/**
 * get_min function
 */
template<class K, class V, class Comp>
typename BST<K,V,Comp>::node_type* BST<K,V,Comp>::get_min() const noexcept {
    if (root == nullptr) return nullptr; //if the tree is empty, return nullptr
    node_type* current = root.get();
    while (current->left_child.get()) {   //do down to the left as much as possible
        current = current->left_child.get();
    }
    return current;
}

/**
 * find function
 */
template<class K, class V, class Comp>
typename BST<K,V,Comp>::iterator BST<K,V,Comp>::find(const key_type key) const noexcept {
    node_type* current = root.get();
    while (current) {
        key_type curr_key = current->data.first;
        if (!compare(curr_key, key) && !compare(key, curr_key)) {   //if current node has sought-after key, return an iterator to it
            return iterator{current};
        }
        else if (compare(key, curr_key)) {    //if greater, proceed in the left subtree
            current = current->left_child.get();
        }
        else {    //if smaller, proceed in the right subtree
            current = current->right_child.get();
        }
        return end();    //if not found, return an iterator to null node
    }
    return end();
}


template<class K, class V, class Comp>
void BST<K,V,Comp>::insert(const key_type& key, const value_type& value){

    if (root == nullptr){ //check if the BST is empty
    
	root = (std::unique_ptr<node_type>) new node_type{key, value, nullptr};
	return;
    }

    node_type *previous_node{root.get()}; //initialize previous node to root
    node_type *current_node{root.get()}; //initilize also the current node ptr to root
    while (current_node) {

	key_type current_key{current_node->data.first};
        if (!compare(current_key, key) && !compare(key, current_key)) { //if the key is already in the tree update the value
	    current_node->data.second = value;
	    break;
        }
        else if (compare(key, current_key)) { // if the new key is smaller go to left subtree
	    previous_node = current_node;
            current_node = current_node->left_child.get();
        }
        else {    //if new key is bigger go to in the right subtree
	    previous_node = current_node;
            current_node = current_node->right_child.get();
        }
    }
    auto& child = (compare(key, previous_node->data.first)) ? previous_node->left_child : previous_node->right_child;
    child = (std::unique_ptr<node_type>) new node_type{key, value, previous_node};

}
template<class K, class V, class Comp>
void BST<K,V,Comp>::insert( const node_type& subtree){

    insert(subtree.data); //copy data in target to the new tree
    if (subtree.left_child)
	insert(*subtree.left_child); //copy left subtree
    if (subtree.right_child)
	insert(*subtree.right_child); //copy right subtree
}

template <class K, class V, class Comp>
void BST<K,V,Comp>::insert_median(std::vector<pair_type>& vect, const size_t lo, const size_t hi){

    if (hi-lo == 1){
    
	insert(vect[lo]);
	insert(vect[hi]);
	return;
    }
    if (hi == lo){
    
	insert(vect[lo]);
	return;
    }
    
    size_t mid = lo + ((hi - lo) >> 1);
    insert(vect[mid]);
    insert_median (vect, lo, mid - 1);
    insert_median (vect,mid + 1, hi);
}
template<class K, class V, class Comp>
void BST<K,V,Comp>::balance(){


    std::vector<pair_type> pairs;
    for (const auto& x : *this)
	pairs.push_back(x);
    clear();
    insert_median(pairs, 0, pairs.size() - 1);
}


template<class K, class V, class Comp>
typename BST<K,V,Comp>::value_type& BST<K,V,Comp>::operator[](const key_type& arg_key) {

    iterator iter = find(arg_key);
    if (iter != end())
	return (*iter).second;
    insert(pair_type{arg_key, value_type{}});
    return (*find(arg_key)).second;
}


template<class K, class V, class Comp>
const typename BST<K,V,Comp>::value_type& BST<K,V,Comp>::operator[](key_type&& arg_key) const {
    iterator iter = find(arg_key);
    if (iter != end()) {
        return (*iter).second;
    }
    throw std::out_of_range{"const operator[] trying to access key not present in given BST"};
}

/**
 * Overload of the operator<<, allows to print
 * the key: value pairs of the tree in-order.
 */
template<class K, class V, class Comp>
std::ostream& operator<<(std::ostream& os, const BST<K,V,Comp>& tree) {
    for (const auto& x : tree) {
        os << x.first << ": " << x.second << std::endl;    //iterate in order and print the key: value pairs
    }
    return os;
}


#endif
