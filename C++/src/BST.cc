#include <BST.h>


template<class K, class V, class Comp>
node_type* BST<K,V,Comp>::get_min() const {
    if (root == nullptr) return nullptr; //if the tree is empty, return nullptr
    node_type* current = root.get();
    while (current->get_left().get()) {   //do down to the left as much as possible
        current = current->get_left().get();
    }
    return current;
}


template<class K, class V, class Comp>
iterator BST<K,V,Comp>::find(key_type key) const {
    node_type* current = root.get();
    while (current) {
        key_type curr_key = current->get_data().first;
        if (!compare(curr_key, key) && !compare(key, curr_key)) {   //if current node has sought-after key, return an iterator to it
            return iterator{current};
        }
        else if (compare(key, curr_key)) {    //if greater, proceed in the left subtree
            current = current->get_left().get();
        }
        else {    //if smaller, proceed in the right subtree
            current = current->get_right().get();
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

    
}
