#include <BST.h>
#include <iterator>


template<class K, class V, class Comp>
class BST<K,V,Comp>::BST_iterator : public std::iterator<std::forward_iterator_tag, pair_type>{

    /**iterator class, compliant with the STL*/

        node_type* current;

    public:
        BST_iterator(node_type* n) : current{n} {}

        pair_type& operator*() const {return current->get_data();} /**dereferencing operator, returns an std::pair<const K,V>*/

        BST_iterator& operator++() {
        /**pre-increment operator, if the current node has a right child, go down right
          *and then as much to the left as possible, then return. Otherwise, go up until
          *you reach the root or you find a node that is not the right child of its parent*/
            if (current->get_right().get() != nullptr) {
                current = current->get_right().get();
                while (current->get_left().get()) {
                    current = current->get_left().get();
                }
                return *this;
            }
            auto p = current->get_parent();
            while (p != nullptr && current == p->get_right().get()) {
                current = p;
                p = p->get_parent();
            }
            current = p;
            return *this;
        }

        bool operator==(const BST_iterator& other) {return current == other.current;} /**equality tests whether two iterators share the same current node*/
        bool operator!=(const BST_iterator& other) {return !(*this==other);}
};


template<class K, class V, class Comp>
class BST<K,V,Comp>::BST_const_iterator : BST<K,V,Comp>::BST_iterator {
    using base = BST<K,V,Comp>::BST_iterator;
    /**populating with the functions of the iterator class, with the
      *exception of the dereferencing that is const as appropriate*/
    using base::BST_iterator;
    const pair_type& operator*() const {return base::operator*();}
    using base::operator++;
    using base::operator==;
    using base::operator!=;
};