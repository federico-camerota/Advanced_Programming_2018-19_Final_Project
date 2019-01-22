#include <BST.h>


template<class K, class V, class Comp>
node_type* BST<K,V,Comp>::get_min() const {
    /** returns a pointer to the node having the minimum value.
      * If the tree is empty, return nullptr, otherwise go left as much as you can. */
    if (root == nullptr) return nullptr;
    node_type* current = root.get();
    while (current->get_left().get()) {
        current = current->get_left().get();
    }
    return current;
}


template<class K, class V, class Comp>
iterator BST<K,V,Comp>::find(key_type key, node_type* node) const {
    /** returns an iterator to the node corresponding to the input key, end()
      * if it is not found. Exploits the sorted nature of the keys to recursively
      * move down from the root. */
    if (node == nullptr) {
        return end();
    }
    key_type curr_key = node->get_data().first;
    if (!compare(curr_key, key) && !compare(key, curr_key)) {
        return iterator{node};
    }
    else if (compare(key, curr_key)) {
        return find(key, node->get_left().get());
    }
    else {
        return find(key, node->get_right().get());
    }
}
