#include "BST.h"
#include <iostream>
#include <string>
#include <stdexcept>

namespace BST_testing{

    std::vector<std::pair<int,std::string>> Tester::init_test() const noexcept {
        std::vector<int> keys{1, 3, 4, 6, 7, 8, 10, 13, 14};
        std::vector<std::pair<int,std::string>> pairs;
        for (auto x : keys) pairs.push_back(std::pair<int,std::string>{x, std::to_string(x)});
        return pairs;
    }

    void Tester::test() const {

	bst_default_ctor();
	bst_insert();
	if (bst_copy_ctor()) {
	    bst_deep_copy();
        }
	bst_move_ctor();
	test_move_copy_assignment();
	test_iterator();
	test_find();
	bst_balance();
        test_clear();
    }

    bool Tester::bst_default_ctor() const noexcept {

	std::cout << "** Testing BST default constructor **" << std::endl;
	BST<std::string,int> bst{};
	//test that root is nullptr and that compare is of type
	//std::less
	bool result = (bst.root == nullptr && typeid(bst.compare) == typeid(std::less<std::string>{}));
	std::cerr << "test " << (result ?  "passed" : "failed") << std::endl;
	return result;
    }

    bool Tester::bst_insert() const {

	std::cout << "** Testing BST insert functions **" << std::endl;
	bst_type bst{};

	bst.insert({8, "eight"});

	bool result{bst.root != nullptr};    //check root is no longer nullptr
	if (result) {
            //check node members are in the expected state
	    bst_type::node_type& root_node{*bst.root};
	    result = result && root_node.data.first == 8 && root_node.data.second == "eight";
	    result = result && root_node.left_child == nullptr && root_node.right_child == nullptr;
	    result = result && root_node.parent == nullptr;
	    std::cerr << "root node test " << (result ?  "passed" : "failed") << std::endl;
	    if (result){

		bst.insert(10, "ten");
		result = result && root_node.right_child != nullptr;
		if (result){
                    //check node members are in the expected state
		    bst_type::node_type& right_node{*root_node.right_child};
		    result = result && right_node.data.first == 10 && right_node.data.second == "ten";
		    result = result && right_node.left_child == nullptr && right_node.right_child == nullptr;
		    result = result && right_node.parent == &root_node;
		}
		std::cerr << "right node test " << (result ?  "passed" : "failed") << std::endl;
		bst.insert(3, "three");
		result = result && root_node.left_child != nullptr;
		if (result){
		    //check node members are in the expected state
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

    bool Tester::bst_copy_ctor() const {
    
	std::cout << "** Testing BST copy constructor **" << std::endl;
	bst_type bst{};
	bst.insert({8, "eight"});
	bst.insert(10, "ten");
	bst.insert(3, "three");

	bst_type copy{bst};
	bool result{copy.root != nullptr};    //check copy is not empty
	if (result){
            // check node is in the expected state
	    bst_type::node_type& root_node{*copy.root};
	    result = result && root_node.data.first == 8 && root_node.data.second == "eight";
	    result = result && root_node.parent == nullptr;
	    std::cerr << "root node test " << (result ?  "passed" : "failed") << std::endl;
	    if (result){

		result = result && root_node.right_child != nullptr;
		if (result){
		    //check node is in the expected state
		    bst_type::node_type& right_node{*root_node.right_child};
		    result = result && right_node.data.first == 10 && right_node.data.second == "ten";
		    result = result && right_node.left_child == nullptr && right_node.right_child == nullptr;
		    result = result && right_node.parent == &root_node;
		}
		std::cerr << "right node test " << (result ?  "passed" : "failed") << std::endl;
		result = result && root_node.left_child != nullptr;
		if (result){
		    //check node is in the expected state
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

    bool Tester::bst_deep_copy() const {
    
	std::cout << "** Testing BST deep copy **" << std::endl;
	bst_type bst{};
	bst.insert({8, "eight"});
	bst.insert(10, "ten");
	bst.insert(3, "three");

	bst_type copy{bst};    //change something in the copied tree
	copy.root->data.second = "changed";
	copy.root->right_child->data.second = "changed";
	copy.root->left_child->data.second = "changed";

	bool result{bst.root->data.second == "eight"};    //check nothing has been changed in the original tree
	result = result && bst.root->right_child->data.second == "ten";
	result = result && bst.root->left_child->data.second == "three";

	result = result && copy.root->data.second == "changed";
	result = result && copy.root->right_child->data.second == "changed";
	result = result && copy.root->left_child->data.second == "changed";

	std::cerr << "test " << (result ?  "passed" : "failed") << std::endl;
	return result;
    }

    bool Tester::bst_move_ctor() const {
    
	std::cout << "** Testing BST move constructor **" << std::endl;
	bst_type bst{};
	bst.insert({8, "eight"});
	bst.insert(10, "ten");
	bst.insert(3, "three");

	bst_type copy{std::move(bst)};

	bool result{bst.root == nullptr};    //check if original tree has actually been moved
	std::cout << "source test " << (result ? "passed" : "failed") << std::endl;

	result = result && copy.root != nullptr;
	if (result){
            //check if node is in the expected state
	    bst_type::node_type& root_node{*copy.root};
	    result = result && root_node.data.first == 8 && root_node.data.second == "eight";
	    result = result && root_node.parent == nullptr;
	    std::cerr << "copy root node test " << (result ?  "passed" : "failed") << std::endl;
	    if (result){

		result = result && root_node.right_child != nullptr;
		if (result){
		    //check if node is in th expected state
		    bst_type::node_type& right_node{*root_node.right_child};
		    result = result && right_node.data.first == 10 && right_node.data.second == "ten";
		    result = result && right_node.left_child == nullptr && right_node.right_child == nullptr;
		    result = result && right_node.parent == &root_node;
		}
		std::cerr << "copy right node test " << (result ?  "passed" : "failed") << std::endl;
		result = result && root_node.left_child != nullptr;
		if (result){
		    //check if node is in the expected state
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

    bool Tester::test_move_copy_assignment() const {
        std::cout << "** Testing BST move and copy assignments **" << std::endl;
        bst_type bst{};
        bst_type _move{};
        bst_type copy{};
        auto pairs{init_test()};
        for (auto& x : pairs) bst.insert(x);
        std::vector<bst_type::pair_type> copy_nodes;
        std::vector<bst_type::pair_type> move_nodes;

        copy = bst;
        _move = std::move(bst);

        bool result{bst.root == nullptr};    //check is original tree has actually been moved
        std::cout << "source test " << (result ? "passed" : "failed") << std::endl;

        result = result && _move.root != nullptr && copy.root != nullptr;    //check if copied and moved trees are not empty
        for (auto& x : copy) copy_nodes.push_back(x);
        for (auto& x : _move) move_nodes.push_back(x);

        result = result && pairs.size() == copy_nodes.size();    //check if copied tree has same size as original
        std::cerr << "copy size test " << (result ?  "passed" : "failed") << std::endl;
        result = result && pairs.size() == move_nodes.size();    //check if moved tree has same size as original
        std::cerr << "move size test " << (result ?  "passed" : "failed") << std::endl;

        for (std::size_t i{0}; i < pairs.size(); ++i) {    //check if nodes of copied appear in same order
            result = result && copy_nodes[i].first == pairs[i].first && copy_nodes[i].second == pairs[i].second;
            if (!result) break;
        }
        std::cerr << "copy test " << (result ?  "passed" : "failed") << std::endl;

        for (std::size_t i=0; i < pairs.size(); ++i) {    //check if nodes of moved appear in same order
            result = result && move_nodes[i].first == pairs[i].first && move_nodes[i].second == pairs[i].second;
            if (!result) break;
        }
        std::cerr << "move test " << (result ?  "passed" : "failed") << std::endl;

        std::cerr << "overall test " << (result ?  "passed" : "failed") << std::endl;
        return result;
    }

    bool Tester::test_iterator() const {

        std::cout << "** Testing BST_iterator class **" << std::endl;
        bst_type bst{};
        auto pairs{init_test()};
        for (auto& x : pairs) bst.insert(x);

        bool result{true};
        std::size_t i{0};
        for (auto& x : bst) {
            result = result && pairs[i].first == x.first && pairs[i].second == x.second;    //test iteration works and is indeed the in-order one
            if (!result) break;
            else ++i;
        }
        std::cerr << "iterator in-order traversal " << (result ? "passed" : "failed") << std::endl;
        return result;
    }

    bool Tester::test_find() const {

        std::cout << "** Testing find function with balancing **" << std::endl;
        bst_type bst{};
        bool result{true};
        auto pairs{init_test()};
        for (auto& x : pairs) result = result && bst.find(x.first) == bst.end();    //test find returns end() if key not present
        std::cerr << "find with empty tree " << (result ? "passed" : "failed") << std::endl;
        for (auto& x : pairs) {
            bst.insert(x);    //automatically calls balance
            result = result && bst.find(x.first) != bst.end();    //test find does not return end() if key is present
            result = result && (*bst.find(x.first)).first == x.first;    //test if the result is indeed correct
        }
        std::cerr << "find with balancing " << (result ? "passed" : "failed") << std::endl;
        return result;
    }

    bool Tester::bst_balance() const {
    
	std::cout << "** Testing BST balance **" << std::endl;
	bst_type bst{};
        auto pairs{init_test()};
        for (auto& x : pairs) bst.insert(x);

	bst.balance();
	bst_type::node_type *root{bst.root.get()};
	bool result{root->data.first == 7};    //check some if some of the nodes are at their expected position
	result = result && root->left_child->data.first == 3 && root->right_child->data.first == 10;
	result = result && root->left_child->left_child->data.first == 1 && root->left_child->right_child->data.first == 4;
	result = result && root->right_child->left_child->data.first == 8 && root->right_child->right_child->data.first == 13;
	result = result && root->left_child->right_child->right_child->data.first == 6;
	result = result && root->right_child->right_child->right_child->data.first == 14;
	    
	std::cerr << "test " << (result ?  "passed" : "failed") << std::endl;
	return result;
    }

    bool Tester::test_clear() const {

        std::cout << "** Testing clear function **" << std::endl;
        bst_type bst{};
        auto pairs{init_test()};
        for (auto& x : pairs) bst.insert(x);
        bool result{true};
        bst.clear();

        int count{0};
        for (auto& x : bst) {    //test the tree is indeed empty and does not contain any nodes
            ++count;
            (void)x;    //suppress unused variable warning
        }

        result = result && count == 0;
        result = result && bst.root == nullptr;    //test the root has been correctly reset to nullptr
        std::cerr << "test clear " << (result ?  "passed" : "failed") << std::endl;
        return result;
    }
}
