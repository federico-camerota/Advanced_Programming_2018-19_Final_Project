//: include/BST.h

#ifndef __BST_H__
#define __BST_H__

#include <functional>
#include <utility>
#include <memory>


#ifdef __BST_DEV__
/**
 * Namespace containing all the testing tools for BST and
 * related classes.
 */
namespace BST_testing {

    /**
     * The Tester class provides a suit of tests to be performed on the
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
	~BST() = default;

	
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
	 * Insert a key-value pair in the BST.
	 * @param pair the key-value pair to insert
	 */
	void insert(const pair_type& pair){

	    insert(pair.first, pair.second);
	}
	/**
	 * Insert a key-value pair in the BST composed by the given key and value.
	 * @param key the key in the pair
	 * @param value the value in the pair
	 */
	void insert(const key_type& key, const value_type& value);
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
	
	value_type& operator[] (const key_type&) noexcept;
	const value_type& operator[] (key_type&&) const;

};


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

namespace BST_testing{

    class Tester{
    
	public:

	    void test();
	    bool bst_default_ctor();
    };
}

#endif
