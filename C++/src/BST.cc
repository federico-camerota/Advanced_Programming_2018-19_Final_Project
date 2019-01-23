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

template<class K, class V, class Comp>
void BST<K,V,Comp>::insert( const node_type& subtree){
    
    if (subtree == BST::nullnode) //check if target is a nullnode
	return;
    insert(subtree.data); //copy data in target to the new tree
    if (subtree.left_child)
	insert(*subtree.left_child); //copy left subtree
    if (subtree.right_child)
	insert(*subtree.right_child); //copy right subtree
}

template<class K, class V, class Comp>
void BST<K,V,Comp>::insert(const key_type& key, const value_type& value){

    if ((auto iter = find(key_type)) != end())
	*iter.data = {key_type, value_type};
    else{
    
	node_type *current_node{root.get()};
	node_type *new_node{new node_type{key, value, nullptr}};
	if (current_node == BST<K,V,Comp>::nullnode){ //check if the BST is empty 
	
	    current_node->parent=new_node; //set the new root node as parent of the nullnode
	    new_node.right = (std::uniq_ptr<node_type>) root.release();//put the nullnode on the 
								       //right child of the new node
	    root = (std::uniq_ptr<node_type>) new_node;//put the new node in root
	    return;
	}
	while (true){
	
	    auto& next_node{ (*current_node < *new_node) ? current_node->left_child : current_node->right_child };
	    if (next_node == nullptr){ //found position in the tree for the new_node
	    
		next_node = (std::uniq_ptr<node_type>) new_node;//set new_node as child of 
								 //current_node	
		new_node->parent = current_node;//update parent member of new_node
		return;
	    }
	    if (*next_node == BST<K,V,Comp>::nullnode){
	    
		new_node->right_child = next_node.release();//put the nullnode as new_node right
							    //child
		new_node->parent = current_node;//update new_node parent member
		next_node = new_node;//put new_node as right child of current node
		return;
	    }
	   current_node = new_node; 
	}
    }
}
