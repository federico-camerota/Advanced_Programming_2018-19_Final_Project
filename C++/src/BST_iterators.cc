#include <BST.h>
#include <iterator>

namespace {
template<class K, class V>
class BST_iterator : public std::iterator<std::forward_iterator_tag, std::pair<const K,V>>{

    /**iterator class, compliant with the STL*/
        using typename BST<K,V>::pair_type;
        using node_type=BST_node<K,V>;

        node_type* current;

    public:
        BST_iterator(node_type* n) : current{n} {}

        pair_type& operator*() const {return current->data;} /**dereferencing operator, returns an std::pair<const K,V>*/

        BST_iterator& operator++() {
        /**pre-increment operator, if the current node has a right child, go down right
          *and then as much to the left as possible, then return. Otherwise, go up until
          *you reach the root or you find a node that is not the right child of its parent*/
            if (current->right_child != nullptr) {
                current = current->right_child.get();
                while (current->left_child.get()) {
                    current = current->left_child.get();
                }
                return *this;
            }
            node_type* p = current->parent;
            while (p != nullptr && current == p->right_child.get()) {
                current = p;
                p = p->parent;
            }
            current = p;
            return *this;
        }

        bool operator==(const BST_iterator& other) {return current == other.current;} //tests whether two iterators share the same current node
        bool operator!=(const BST_iterator& other) {return !(*this==other);}
};
}

namespace {
template<class K, class V>
class BST_const_iterator : public BST_iterator<K,V> {
    using base = ::BST_iterator<K,V>;
    using typename BST<K,V>::pair_type;
    /**populating with the functions of the iterator class, with the
      *exception of the dereferencing that is const as appropriate*/
    using base::BST_iterator;
    const pair_type& operator*() const {return base::operator*();}
    using base::operator++;
    using base::operator==;
    using base::operator!=;
};
}
