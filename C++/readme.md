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

The BST class is templated to the type of the key, the value, and the operator used for comparisons, which has been defaulted to std::less. The class is endowed with three private classes and structs, BST_node, BST_iterator and BST_const_iterator, which have been left private since, from a conceptual point of view, it does not make sense for them to exist outside and independently of a BST class. Moreover, we want to keep our object in a meaningful state, by hiding to the user all the internal workings of our class and how are data organized, which also improves the maintainability of our code. This is an instance of the concept of "data hiding". On the other side, since they are not templated to the same types of the class (we are missing the comparison type), these three classes have been implemented in an appropriate namespace.

## 2. Iterator class
The class has one private member, that points to a node. In order to implement the Iterator Pattern, it provides the overload of the operator* (which returns an std::pair<key_type, value_type), the overload of the pre-increment ++ (which basically looks for the successor of the current node), and the overload of the operator!=. In addition, the class has been made compliant with the STL by inheriting from std::iterator defined in the <iterator> tag, so that an algorithm of the STL might be invoked on it.

## 3. Const_iterator class
The class inherits from BST_iterator and is populated with the constructor and all the operators of the parent, with the exception of the overload of the operator* whose return type has been marked as const, as appropriate. In fact, a separate const_iterator class is needed, because the aforementioned overload would not be possible in the iterator class alone, since the original operator* was marked as const at the end of the function, and function overloading would not have worked on the two versions.
