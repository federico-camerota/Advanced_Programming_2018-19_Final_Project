#include "BST.h"
#include <iostream>
#include <string>

namespace BST_testing{

    void Tester::test(){
    

	bst_default_ctor();	
	bst_insert();
	if(bst_copy_ctor())
	    bst_deep_copy();
	
    }

    bool Tester::bst_default_ctor(){
    
	std::cerr << "** Testing BST default constructor **" << std::endl;
	BST<std::string,int> bst{};
	//test that root is nullptr and that compare is of type
	//std::less
	bool result = (bst.root == nullptr && typeid(bst.compare) == typeid(std::less<std::string>{}));
	std::cerr << "test " << (result ?  "passed" : "failed") << std::endl;
	return result;
    }

    bool Tester::bst_insert(){
    
	using bst_type = BST<int, std::string>;

	std::cerr << "** Testing BST insert functions **" << std::endl;
	bst_type bst{};

	bst.insert({8, "eight"});

	bool result{bst.root != nullptr};
	if (result){

	    bst_type::node_type& root_node{*bst.root};
	    result = result && root_node.data.first == 8 && root_node.data.second == "eight";
	    result = result && root_node.left_child == nullptr && root_node.right_child == nullptr;
	    result = result && root_node.parent == nullptr;
	    std::cerr << "root node test " << (result ?  "passed" : "failed") << std::endl;
	    if (result){

		bst.insert(10, "ten");
		result = result && root_node.right_child != nullptr;
		if (result){
		
		    bst_type::node_type& right_node{*root_node.right_child};
		    result = result && right_node.data.first == 10 && right_node.data.second == "ten";
		    result = result && right_node.left_child == nullptr && right_node.right_child == nullptr;
		    result = result && right_node.parent == &root_node;
		}
		std::cerr << "right node test " << (result ?  "passed" : "failed") << std::endl;
		bst.insert(3, "three");
		result = result && root_node.left_child != nullptr;
		if (result){
		
		    bst_type::node_type& left_node{*root_node.left_child};
		    result = result && left_node.data.first == 3 && left_node.data.second == "three";
		    result = result && left_node.left_child == nullptr && left_node.right_child == nullptr;
		    result = result && left_node.parent == &root_node;
		}
		std::cerr << "left node test " << (result ?  "passed" : "failed") << std::endl;
	    }
	}
	std::cerr << "overall test " << (result ?  "passed" : "failed") << std::endl;
	return result;
    }

    bool Tester::bst_copy_ctor(){
    
	std::cout << "** Testing BST copy constructor **" << std::endl;
	using bst_type = BST<int, std::string>;
	bst_type bst{};
	bst.insert({8, "eight"});
	bst.insert(10, "ten");
	bst.insert(3, "three");

	bst_type copy{bst};
	bool result{copy.root != nullptr};
	if (result){

	    bst_type::node_type& root_node{*copy.root};
	    result = result && root_node.data.first == 8 && root_node.data.second == "eight";
	    result = result && root_node.parent == nullptr;
	    std::cerr << "root node test " << (result ?  "passed" : "failed") << std::endl;
	    if (result){

		result = result && root_node.right_child != nullptr;
		if (result){
		
		    bst_type::node_type& right_node{*root_node.right_child};
		    result = result && right_node.data.first == 10 && right_node.data.second == "ten";
		    result = result && right_node.left_child == nullptr && right_node.right_child == nullptr;
		    result = result && right_node.parent == &root_node;
		}
		std::cerr << "right node test " << (result ?  "passed" : "failed") << std::endl;
		result = result && root_node.left_child != nullptr;
		if (result){
		
		    bst_type::node_type& left_node{*root_node.left_child};
		    result = result && left_node.data.first == 3 && left_node.data.second == "three";
		    result = result && left_node.left_child == nullptr && left_node.right_child == nullptr;
		    result = result && left_node.parent == &root_node;
		}
		std::cerr << "left node test " << (result ?  "passed" : "failed") << std::endl;
	    }
	}
	std::cerr << "overall test " << (result ?  "passed" : "failed") << std::endl;
	return result;
    }

    bool Tester::bst_deep_copy(){
    
	std::cout << "** Testing BST deep copy **" << std::endl;
	using bst_type = BST<int, std::string>;
	bst_type bst{};
	bst.insert({8, "eight"});
	bst.insert(10, "ten");
	bst.insert(3, "three");

	bst_type copy{bst};
	copy.root->data.second = "changed";
	copy.root->right_child->data.second = "changed";
	copy.root->left_child->data.second = "changed";

	bool result{bst.root->data.second == "eight"};
	result = result && bst.root->right_child->data.second == "ten";
	result = result && bst.root->left_child->data.second == "three";

	result = result && copy.root->data.second == "changed";
	result = result && copy.root->right_child->data.second == "changed";
	result = result && copy.root->left_child->data.second == "changed";

	std::cerr << "test " << (result ?  "passed" : "failed") << std::endl;
	return result;
    }


}
