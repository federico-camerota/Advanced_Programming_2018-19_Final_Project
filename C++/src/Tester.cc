#include "BST.h"
#include <iostream>
#include <string>

namespace BST_testing{

    void Tester::test(){
    

	bst_default_ctor();	
	bst_insert();
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
    
	using bst_type = BST<std::string, int>;

	std::cerr << "** Test BST insert functions **" << std::endl;
	bst_type bst{};

	bst.insert("eight", 8);
	
	if (bst.root != nullptr){
	
	    bst_type::node_type& root_node{*bst.root};

	    if (root_node.data.first == "eight" && root_node.data.second == 8){
		if (root_node.left_child == nullptr && root_node.right_child == nullptr){
		
		    if (root_node.parent == nullptr){
			std::cout << "Test passed" << std::endl;
			return true;
		    }
		}
	    }
	}
	std::cout << "Test failed" << std::endl;
	return false;
    }
}
