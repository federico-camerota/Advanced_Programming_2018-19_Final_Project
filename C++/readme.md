# Report - C++

## 0. Usage
To compile the code and perform all the designed tests use:
```bash
make dev
```
an executable named `bst_test` will be created.
Instead, to compile it and perform a benchmark against `std::map` use:
```bash
make benchmark
```
or just:
```bash
make
```
an executable named `bst_benchmark` will be created.

## 1. Overview
The code comprises a header file, BST.h (under /include/) where a full templated binary search tree class has been defined and implemented. Under the /src/ folder you can find a Tester.cc class, defined in its own namespace, which is in charge of performing all the tests on instances of the BST class.

The BST class is templated to the type of the key, the value, and the operator used for comparisons, which has been defaulted to std::less. The class is endowed with three private classes and structs, BST_node, BST_iterator and BST_const_iterator, which have been left private since, from a conceptual point of view, it does not make sense for them to exist outside and independently of a BST class. Moreover, we want to keep our object in a meaningful state, by hiding to the user all the internal workings of our class and how are data organized, which also improves the maintainability of our code. This is an instance of the concept of "data hiding". On the other side, since they are not templated to the same types of the class (we are missing the comparison type), these three classes have been implemented in an appropriate namespace. As a final note, the key to each std::pair<key_type,value_type> (which is meant to store node data) has been marked as const, mimicking the same behavior of std::map. In fact, allowing the user to change one of the keys would damage the balancement property of a BST.

## 2. Iterator class
The class has one private member, that points to a node. In order to implement the Iterator Pattern, it provides the overload of the operator* (which returns an std::pair<key_type, value_type), the overload of the pre-increment ++ (which basically looks for the successor of the current node), and the overload of the operator!=. In addition, the class has been made compliant with the STL by inheriting from std::iterator defined in the <iterator> tag, so that an algorithm of the STL might be invoked on it.

## 3. Const_iterator class
The class inherits from BST_iterator and is populated with the constructor and all the operators of the parent, with the exception of the overload of the operator* whose return type has been marked as const, as appropriate. In fact, a separate const_iterator class is needed, because the aforementioned overload would not be possible in the iterator class alone, since the original operator* was marked as const at the end of the function, and function overloading would not have worked on the two versions.

## 4. Member functions
begin and end, const and non-const, cbegin and cend - these functions allow to traverse the BST using a range for-loop, following the in-order traversal dictated by the iterator. The const versions of begin and end allow traversal of a const instance of a BST, and return const_iterators, not iterators. cbegin() and cend() might be useful if you want to use a const_iterator for a non-const tree instance, for example if you want to call an algorithm of the STL on the tree by making sure its members will not be modified. Finally, notice the end functions return an iterator to nullptr.

find - returns an iterator to the node having the sought-after key, otherwise end() is returned 

## 5. Copy and move semantics
Copy constructor - 
Move constructor -
Copy assignment - this overloads the operator= with an l-value reference (marked as const) to a BST object as argument, clears any memory used, creates a copy with the copy constructor and moves the copy onto this by calling move semantics.
Move assignemnt - this overloads the operator= with an r-value reference to a BST as argument, whose root is then moved to the root of this.

Since move semantics does not allocate any new memory, it has already been successfully allocated and we are simply moving it, so we can mark them an noexcept. Of course, in this case, const does not apply to the input tree since the move semantics leave the object in an undefined (but still in such a state that a destructor can be called successfully).
