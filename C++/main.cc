#include "BST.h"
#include <string>
#include <array>
#include <map>
#include <random>
#include <chrono>
#include <iostream>

int main(){

#ifdef __BST_DEV__
    BST_testing::Tester t;
    t.test();
#else
    using bst_type = BST<size_t, std::string>;

    const size_t N{10};
    const size_t k{6};
    const int searches{20};
    
    bst_type bst{};
    std::map<size_t, std::string> map{};

    std::array<long int, searches> bst_times, map_times;
    std::random_device rand_dev;
    std::mt19937 generator{rand_dev()};
    std::uniform_int_distribution<size_t> rand;


    std::cout << "** Unbalanced test **" << std::endl;
    for (size_t run{0}; run < k; run++){
    
	size_t size{N};
	for (size_t j{0}; j < run; j++)
	    size *= N;

	std::cout << "Running with size = " << size << std::endl;

	for (size_t j{1}; j <= size; j++){
	
	    size_t num{rand(generator)};
	    bst.insert(num, std::to_string(num));
	    map.insert(std::map<size_t,std::string>::value_type{num, std::to_string(num)});
	}

	for (int search{0}; search < searches; search++){
	
	    size_t item{rand(generator)};
	    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	    bst.find(item);
	    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	    bst_times[search] = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
	    start = std::chrono::high_resolution_clock::now();
	    map.find(item);
	    end = std::chrono::high_resolution_clock::now();
	    map_times[search] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	}

	std::cout << "bst_times: [";
	for (auto x : bst_times)
	    std::cout << x << ", ";
	std::cout << "\b\b" << "]" << std::endl;
	std::cout << "map_times: [";
	for (auto x : map_times)
	    std::cout << x << ", ";
	std::cout << "\b\b" << "]" << std::endl;

	bst.clear();
	map.clear();
    }

    std::cout << "** Balanced test **" << std::endl;
    for (size_t run{0}; run < k; run++){
    
	size_t size{N};
	for (size_t j{0}; j < run; j++)
	    size *= N;

	std::cout << "Running with size = " << size << std::endl;

	for (size_t j{1}; j <= size; j++){
	
	    size_t num{rand(generator)};
	    bst.insert(num, std::to_string(num));
	    map.insert(std::map<size_t,std::string>::value_type{num, std::to_string(num)});
	}
	bst.balance();

	for (int search{0}; search < searches; search++){
	
	    size_t item{rand(generator)};
	    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	    bst.find(item);
	    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	    bst_times[search] = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();
	    start = std::chrono::high_resolution_clock::now();
	    map.find(item);
	    end = std::chrono::high_resolution_clock::now();
	    map_times[search] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	}

	std::cout << "bst_times: [";
	for (auto x : bst_times)
	    std::cout << x << ", ";
	std::cout << "\b\b" << "]" << std::endl;
	std::cout << "map_times: [";
	for (auto x : map_times)
	    std::cout << x << ", ";
	std::cout << "\b\b" << "]" << std::endl;

	bst.clear();
	map.clear();
    }

#endif

}
