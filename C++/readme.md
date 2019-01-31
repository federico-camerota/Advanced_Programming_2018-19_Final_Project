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
an executable named `bst_benchmark` will be created. The above benchmark consists in performing 50 searches using the `find` function in a randomly built BST and has been performed using trees of size 
3^k, for k = 1, ..., 15. First the test is done using the tree as it is built and then balancing it. The obtained results are plotted in the following images
<img src="images/unbalanced_times.png" alt="drawing" width="800" height="600"/>
<img src="images/balanced_times.png" alt="drawing" width="800" height="600"/>

In the images, the red cuve represents the times obtained using our data structure while the blue one the times of `std::map`.
From this results we can see that, when the BST is balanced using our algorithm the performance is quite similar to the one obtained using the standard library `std::map` data structure.

The balance tree and `std::map` should show a search time that scales as `log(n)`, where `n` is the number of nodes in the tree. Due to the properties of the `log` function the ratio `log(n^k)/log(n)` is 
    equal to `k`. So, we plotted in the following image this ratio using the obtained results where `n` is set to 3 and k goes from 1 to 15.
<img src="images/balanced_ratio.png" alt="drawing" width="800" height="600"/>

It can be seen that the two data structures show a similar behavior. However, this is not the trend one would expect from theory. In fact, we should see approximatively a straight line. 
Even though the experimental observations seem not to support the theory they reflect the memory hierarchy of the machine. That is, when we perform this benchmark using a small number of nodes, probably
both structures fit in the cache while for bigger values of k the structures don't fit in the cache any more. Due to this fact, the time it takes on avarage to find an element in a bigger tree increases 
not only beacause the data structure is bigger but also because it is also farther away from the CPU.

## 1. Overview
The code comprises a header file, BST.h (under /include/) where a full templated binary search tree class has been defined and implemented. Under the /src/ folder you can find a Tester.cc class, defined in its own namespace, which is in charge of performing all the tests on instances of the BST class.

The BST class is templated to the type of the key, the value, and the operator used for comparisons, which has been defaulted to `std::less`. 
Three other classes have been declared, `BST_node`, `BST_iterator` and `BST_const_iterator`, in an unnamed namespace since, from a conceptual point of view, it does not make sense for them to exist outside and independently of a BST class. Additionally, we want the internal workings of our class to be kept hidden to the user. This is an instance of the concept of "data hiding".
Furthermore, by doing so, they are not templated to comparison type used in BST. If they had been defined as private to the class, a copy of them would be generated for each different comparison that happens to be used, uselessly enlarging the binary.

The BST class also provides the following aliases:
1. `key_type` that is an alias for the type of keys.
2. `value_type` that is an alias for the type of values associated to keys.
3. `pair_type` that is an alias for `std::pair<const key_type, value_type>`.
4. `iterator` that is an alias for the `BST_iterator` class templated on the same key-value parameters as the BST.
5. `const_iterator` that is an alias for the `BST_const_iterator` class.

As a final note, the key to each `pair_type` (which is meant to store node data) has been marked as const, mimicking the same behavior of `std::map`. In fact, allowing the user to change one of the keys would damage the balancement property of a BST.


## 2. Iterator class
The class has one private member, that points to a node. In order to implement the Iterator Pattern, it provides the overload of the `operator*` (which returns an `std::pair<const key_type, value_type>`), the overload of the pre-increment `operator++` (which basically looks for the successor of the current node), and the overload of the `operator!=`. In addition, the class has been made compliant with the STL by inheriting from `std::iterator` defined in the `<iterator>` header.

## 3. Const_iterator class
The class inherits from `BST_iterator` and is populated with the constructor and all the operators of the parent, with the exception of the overload of the `operator*` which returns a `const` reference, as appropriate. In fact, a separate `const_iterator` class is needed, because the aforementioned overload would not be possible in the iterator class alone, since the original `operator*` was marked as `const` at the end of the function, and function overloading would not have worked on the two versions. As a result, we can now work with const instances of the class.

## 4. Member functions
The BST class has the following member functions:
* `begin` and `end`, const and non-const, `cbegin` and `cend` - these functions allow to traverse the BST using a range for-loop, following the in-order traversal dictated by the iterator. The const versions of begin and end allow traversal of a const instance of a BST, and return const_iterators, not iterators. `cbegin()` and `cend()` might be useful if you want to use a const_iterator for a non-const tree instance, for example if you want to call an algorithm of the STL on the tree by making sure its members will not be modified. Finally, notice the end functions return an iterator to nullptr.
* `insert` - that is declared in three different ways to allow the insertion in the BST of a key-value pair or a full subtree. In case the key is already in the tree the associated value it's updated.
* `balance` - a function that balances the BST. The structure is rebalanced by creating a new tree and recursively inserting into it the median (with respect to the key ordering) key-value pair.
* `find` - returns an iterator to the node having the sought-after key, otherwise `end()` is returned.
* `clear` - deletes all the elements in the BST.
* `operator[]` - both `const` and `non-const` versions have been implemented. In the former (which is supposed to be called on const instances of BST), if the key is not present, an std::out_of_range exception is thrown with a meaningful message. In the latter, if the key is not present, insert is called on the lookup key and the value is default-initialized.  


## 5. Copy and move semantics
The BST class implements copy and move semantics through the following functions:
* Copy constructor - creates a deep copy of the given BST by recursively coping the structure starting at its root node.
* Move constructor - that steals the resources of the given rvalue referenced BST by swapping the root nodes of the two structures.
* Copy assignment - this overloads the `operator=` with an l-value reference (marked as const) to a BST object as argument. It  clears any memory used, creates a copy with the copy constructor and moves the copy onto this by calling move semantics.
* Move assignment - this overloads the `operator=` with an r-value reference to a BST as argument, whose root is then moved to the root of this.

Since move semantics does not allocate any new memory (it has already been successfully allocated and we are simply moving it) we can mark operators implementing such semantics as `noexcept`. Of course, in this case, `const` does not apply to the input tree since move semantics leaves the object in an undefined state (but still in such a state that a destructor can be called successfully).

## 6. Testing tools
To perform different tests on BSTs and related objects we declared a `Tester` class. This class is declared in a specific namespace and included in the header file only if compiled with the 
`__BST_DEV__` macro defined. If that macro is defined, the above class is declared as `friend` in BST to grant it access to private members and ease testing. Furthermore, being declared in the same header
file, the `Tester` class has access to the other utility classes used by BST.
The public function `test` allows to automatically call all the test in succession. Tests are performed on empty BSTs, copy and move semantics (checking also that a deep copy has effectively been performed), the iterator, as well as the insert, balance, find and clear functions.

## 7. Documentation
The source code has been well documented throughout the project. Under the folder /doc/ it is possible to find a Doxyfile ready to be executed with `doxygen Doxyfile`.
