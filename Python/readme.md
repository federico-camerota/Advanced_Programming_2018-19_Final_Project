# Report - Python
The class PostcardList has been implemented, and passes all the tests.

## Functions
writeFile - opens self._file in write mode and writes the content of self._{date, from, to} as a human-readable string.
readFile - loops through the lines of the input file and appends them to self._postcards, then call parsePostcards method to
parse them. Notice the other members need to be reset.
updateFile - as writeFile but self._file is opened in append mode.
updateLists - as readFile but appending to self._postcards.

Notice that in all of the above functions the handling of files went through a context manager. Since Python lacks in the power
of destructors to implement RAII, context managers are a very useful tool in that every resource acquired within them is realeased
on exit.

‘getNumberOfPostcards‘ - can be easily achieved by calling len, which under the hood calls the __len__ dunder method.
