#include "BST.h"
#include <iostream>
#include <string>
#include <stdexcept>

namespace BST_testing{

    void Tester::test(){

	bst_default_ctor();	
	bst_insert();
	if(bst_copy_ctor())
	    bst_deep_copy();
	bst_move_ctor();
	
	//other tests
	
	bst_balance();
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

    bool Tester::bst_move_ctor(){
    
	std::cout << "** Testing BST move constructor **" << std::endl;
	using bst_type = BST<int, std::string>;
	bst_type bst{};
	bst.insert({8, "eight"});
	bst.insert(10, "ten");
	bst.insert(3, "three");

	bst_type copy{std::move(bst)};

	bool result{bst.root == nullptr};
	std::cout << "source test " << (result ? "passed" : "failed") << std::endl;

	result = result && copy.root != nullptr;
	if (result){

	    bst_type::node_type& root_node{*copy.root};
	    result = result && root_node.data.first == 8 && root_node.data.second == "eight";
	    result = result && root_node.parent == nullptr;
	    std::cerr << "copy root node test " << (result ?  "passed" : "failed") << std::endl;
	    if (result){

		result = result && root_node.right_child != nullptr;
		if (result){
		
		    bst_type::node_type& right_node{*root_node.right_child};
		    result = result && right_node.data.first == 10 && right_node.data.second == "ten";
		    result = result && right_node.left_child == nullptr && right_node.right_child == nullptr;
		    result = result && right_node.parent == &root_node;
		}
		std::cerr << "copy right node test " << (result ?  "passed" : "failed") << std::endl;
		result = result && root_node.left_child != nullptr;
		if (result){
		
		    bst_type::node_type& left_node{*root_node.left_child};
		    result = result && left_node.data.first == 3 && left_node.data.second == "three";
		    result = result && left_node.left_child == nullptr && left_node.right_child == nullptr;
		    result = result && left_node.parent == &root_node;
		}
		std::cerr << "copy left node test " << (result ?  "passed" : "failed") << std::endl;
	    }
	}
	std::cerr << "overall test " << (result ?  "passed" : "failed") << std::endl;
	return result;
    }

    bool Tester::test_move_copy_assignment() {
        std::cout << "** Testing BST move and copy assignments **" << std::endl;
        using bst_type = BST<int, std::string>;
        bst_type bst{};
        bst_type _move{};
        bst_type copy{};
        std::vector<int> keys{1, 3, 4, 6, 7, 8, 10, 13, 14};
        std::vector<std::string> values;
        for (auto& x : keys) values.push_back(std::to_string(x));
        for (std::size_t i=0; i < keys.size(); ++i) bst.insert(keys[i], values[i]);

        copy = bst;
        _move = std::move(bst);

        bool result{bst.root == nullptr};
        std::cout << "source test " << (result ? "passed" : "failed") << std::endl;

        result = result && _move.root != nullptr && copy.root != nullptr;
        std::vector<bst_type::pair_type> copy_nodes;
        std::vector<bst_type::pair_type> move_nodes;
        std::vector<bst_type::pair_type> original_nodes;
        for (auto& x : bst) original_nodes.push_back(x);
        for (auto& x : copy) copy_nodes.push_back(x);
        for (auto& x : _move) move_nodes.push_back(x);

        result = result && original_nodes.size() == copy_nodes.size();
        std::cerr << "copy size test " << (result ?  "passed" : "failed") << std::endl;
        result = result && original_nodes.size() == move_nodes.size();
        std::cerr << "move size test " << (result ?  "passed" : "failed") << std::endl;

        for (std::size_t i=0; i < original_nodes.size(); ++i) {
            result = result && copy_nodes[i] == original_nodes[i];
            if (!result) break;
        }
        std::cerr << "copy test " << (result ?  "passed" : "failed") << std::endl;

        for (std::size_t i=0; i < original_nodes.size(); ++i) {
            result = result && move_nodes[i] == original_nodes[i];
            if (!result) break;
        }
        std::cerr << "move test " << (result ?  "passed" : "failed") << std::endl;

        std::cerr << "overall test " << (result ?  "passed" : "failed") << std::endl;
        return result;
    }

    bool Tester::test_iterators() {
        using bst_type = BST<int, std::string>;
        std::cout << "** Testing BST_iterator and BST_const_iterator classes **" << std::endl;
	using bst_type = BST<int, std::string>;
        bst_type bst{};
        std::vector<int> keys{1, 3, 4, 6, 7, 8, 10, 13, 14};
        std::vector<std::string> values;
        for (auto& x : keys) values.push_back(std::to_string(x));
        for (std::size_t i=0; i < keys.size(); ++i) bst.insert(keys[i], values[i]);

        auto min{bst.get_min()->data.first - 1};
        bool result{};
        for (auto& x : bst) {
            result = result && x.first > min;
            if (!result) break;
            else min = x.first;
        }
        std::cerr << "in-order traversal " << (result ? "passed" : "failed") << std::endl;

        std::size_t i{0};
        for (auto& x : bst) {
            result = result && keys[i] == x.first && values[i] == x.second;
            if (!result) break;
            else ++i;
        }
        std::cerr << "dereferencing " << (result ? "passed" : "failed") << std::endl;

        for (auto& x : bst) {
            try {
                 x.first = 0;
                 result = result && false;
            }
            catch (...) {
                result = result && true;
            }
        }
        std::cerr << "keys' modifiability " << (result ? "passed" : "failed") << std::endl;

        for (const auto& x : bst) {
            try {
                 x.second = "error";
                 result = result && false;
            }
            catch (...) {
                result = result && true;
            }
        }
        std::cerr << "const iterator " << (result ? "passed" : "failed") << std::endl;
        return result;
    }

    bool Tester::test_find() {

        using bst_type = BST<int, std::string>;
        std::cout << "** Testing find function with balancing **" << std::endl;
        bst_type bst{};
        std::vector<int> keys{1, 3, 4, 6, 7, 8, 10, 13, 14};
        std::vector<std::string> values(9);
        for (auto& x : keys) values.push_back(std::to_string(x));
        bool result{};
        for (auto& x: keys) result = result && bst.find(x) == bst.end();
        std::cerr << "find with empty tree " << (result ? "passed" : "failed") << std::endl;
        for (std::size_t i=0; i < keys.size(); ++i) {
            result = result && bst.find(keys[i]) == bst.end();
            bst.insert(keys[i], values[i]);    //automatically calls balance
            result = result && bst.find(keys[i]) != bst.end();
        }
        std::cerr << "find with balancing " << (result ? "passed" : "failed") << std::endl;
        return result;
    }
    bool Tester::bst_balance(){
    
	std::cout << "** Testing BST balance **" << std::endl;
	using bst_type = BST<int, std::string>;
	bst_type bst{};
	bst.insert({8, "eight"});
	bst.insert(10, "ten");
	bst.insert(3, "three");
	bst.insert(1,"one");
	bst.insert(6,"six");
	bst.insert(4,"four");
	bst.insert(7,"seven");
	bst.insert(14,"fourteen");
	bst.insert(13,"thirteen");

	bst.balance();
	bst_type::node_type *root{bst.root.get()};
	bool result{root->data.first == 7};
	result = result && root->left_child->data.first == 3 && root->right_child->data.first == 10;
	result = result && root->left_child->left_child->data.first == 1 && root->left_child->right_child->data.first == 4;
	result = result && root->right_child->left_child->data.first == 8 && root->right_child->right_child->data.first == 13;
	result = result && root->left_child->right_child->right_child->data.first == 6;
	result = result && root->right_child->right_child->right_child->data.first == 14;
	    
	std::cout << "test " << (result ?  "passed" : "failed") << std::endl;
	return result;
    }
}
