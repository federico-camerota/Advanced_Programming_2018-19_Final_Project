#include <BST.h>
#include <vector>
#include <iostream>
#include <stdexcept>


template<class K, class V, class Comp>
typename BST<K,V,Comp>::node_type* BST<K,V,Comp>::get_min() const noexcept {
    if (root == nullptr) return nullptr; //if the tree is empty, return nullptr
    node_type* current = root.get();
    while (current->left_child.get()) {   //do down to the left as much as possible
        current = current->left_child.get();
    }
    return current;
}


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
}

template<class K, class V, class Comp>
std::ostream& operator<<(std::ostream& os, const BST<K,V,Comp>& tree) {
    for (const auto& x : tree) {
        os << x.first << ": " << x.second << std::endl;
    }
    return os;
}
