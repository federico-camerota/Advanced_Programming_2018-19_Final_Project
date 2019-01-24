#include <BST.h>


template<class K, class V, class Comp>
node_type* BST<K,V,Comp>::get_min() const {
    if (root == nullptr) return nullptr; //if the tree is empty, return nullptr
    node_type* current = root.get();
    while (current->left_child.get()) {   //do down to the left as much as possible
        current = current->left_child.get();
    }
    return current;
}


template<class K, class V, class Comp>
iterator BST<K,V,Comp>::find(const key_type key) const {
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
}


template<class K, class V, class Comp>
void BST<K,V,Comp>::insert( const node_type& subtree){

    insert(*(subtree.data)); //copy data in target to the new tree
    if (subtree.left_child)
	insert(*subtree.left_child); //copy left subtree
    if (subtree.right_child)
	insert(*subtree.right_child); //copy right subtree
}



template<class K, class V, class Comp>
void BST<K,V,Comp>::insert(const key_type& key, const value_type& value){

    if (root == nullptr){ //check if the BST is empty
    
	root = new node_type{key, value, nullptr};
	return;
    }

    node_type* previous_node{root.get()}; //initialize previous node to root
    node_type* current_node{root.get()}; //initilize also the current node ptr to root
    while (current_node) {

	key_type current_key{current_node->data->first};
        if (!compare(current_key, key) && !compare(key, current_key)) { //if the key is already in the tree update the value
	    current_node->data->second = value;
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
    auto& child = (compare(previous_node->data->first, key)) ? previous_node->left_child : previous_node->right_child;
    child = new node_type{key, value, previous_node};

}

/**
 * Utility function to insert median element in a given tree from a vector of pairs
 */
template <class K, class V, class Comp>
static void insert_median(BST<K,V,Comp>& tree, std::vector<K,V>& vect, const size_t lo, const size_t hi){

    if (hi-lo == 1){
    
	tree.insert(vect[lo]);
	tree.insert(vect[hi]);
	return;
    }
    if (hi == lo){
    
	tree.insert(vect[lo]);
	return;
    }
    
    size_t mid = lo + ((hi - lo) >> 1);
    tree.insert(vect[mid]);
    insert_median (tree, vect, lo, mid - 1);
    insert_median (tree, vect,mid + 1, hi);
}
template<class K, class V, class Comp>
void BST<K,V,Comp>::balance(){

    
    std::vector<pair_type> pairs;
    for (const auto& x : *this) 
	pairs.push_back(x);
    clear();
    insert_median(*this, pairs, 0, pairs.size() - 1);
}
